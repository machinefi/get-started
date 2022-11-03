#include <Arduino.h>
#include <Arduino_JSON.h>
#include <NTPClient.h>
#include <PubSubClient.h>
#include "secrets.h"

#ifdef ESP32
    #include <WiFi.h>
    #include <HTTPClient.h>

#endif
#ifdef __SAMD21G18A__
    #include <WiFiNINA.h>
    #include <ArduinoHttpClient.h>
#endif

using namespace std;

const int32_t EVENT_TYPE = 2147483647;

// The button pin
#ifdef __SAMD21G18A__
#define BUTTON_PIN 3    // Pin D3
    // #if SECRET_HTTP_ENABLED
    //     #error "HTTP is not supported for Nano 33 IoT"
    // #endif
#else
#define BUTTON_PIN 35
#endif

// const String httpEndpoint = "/srv-applet-mgr/v0/event/" + String(SECRET_PROJECT_NAME);
const String httpEndpoint = "/anything";
const String url = "http://" + String(SECRET_WEBSTREAM_HOST) + ":" + String(SECRET_WEBSTREAM_PORT) + httpEndpoint;

WiFiClient wifiClient;
WiFiUDP ntpUDP;
PubSubClient mqttClient(wifiClient);
NTPClient timeClient(ntpUDP);

#ifdef ESP32
    HTTPClient httpClient;
#endif
#ifdef __SAMD21G18A__
    HttpClient httpClient(wifiClient, SECRET_WEBSTREAM_HOST, SECRET_WEBSTREAM_PORT);
#endif


/**
 * @brief Creates a JSON object containing the payload with the following shcema:
    {
        "header" : 
        {
            "event_type" : <number>,
            "pub_id" : <string>,
            "pub_time" : <number>,
            "token" : <string>
        },
        "payload" : <string>
    }
*/
JSONVar getPayloadJSON()
{
    // Build the header
    JSONVar header_json;
    header_json["event_type"] = EVENT_TYPE;
    if (SECRET_PUBLISHER_AUTHENTICATION_ENABLED)
    {
        header_json["pub_id"] = SECRET_PUBLISHER_ID;
        header_json["pub_time"] = timeClient.getEpochTime();
        header_json["token"] = SECRET_PUBLISHER_TOKEN;
    }

    JSONVar payload_to_wasm_instance;
    payload_to_wasm_instance["Connections"] = 395;
    payload_to_wasm_instance["Account"] = "610CBDa6f0037B4141A5B949f56479106BeCb1E9";

    JSONVar payload_json;
    payload_json["payload"] = JSON.stringify(payload_to_wasm_instance);
    payload_json["header"] = header_json;

    return payload_json;
}


/**
 * @brief Connects to WiFi
 * 
 */
void initWiFi() 
{
    #if defined(ESP32)
        WiFi.mode(WIFI_STA);
    #endif
    WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASS);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(500);
    }
    Serial.print("\nConnected. IP: ");
    Serial.println(WiFi.localIP());
}


/**
 * @brief Connects to the MQTT broker
 * 
 */
void connectToMqttBroker()
{
    Serial.println("Attempting to connect to the MQTT broker at " + String(SECRET_MQTT_BROKER_HOST) + ":" + String(SECRET_MQTT_BROKER_PORT));
    mqttClient.setServer(SECRET_MQTT_BROKER_HOST, SECRET_MQTT_BROKER_PORT);
    while (!mqttClient.connected())
    {
        String clientId = SECRET_MQTT_CLIENT_ID;
        if (mqttClient.connect(clientId.c_str()))
        {
            Serial.println("Connected to MQTT broker");
        }
        else
        {
            Serial.println("Failed to connect to MQTT broker: " + mqttClient.state());
            Serial.println("Retrying in 2 seconds");
            delay(2000);
        }
    }
}

/**
 * @brief Sends an event using Http
 * 
 */
void sendEventHttp()
{
    String body = JSON.stringify(getPayloadJSON());
    Serial.println("Sending http POST request to " + url + " with body: ");
    Serial.println(body);
    #ifdef ESP32
        httpClient.addHeader("Content-Type", "application/json");
        httpClient.begin(url);
        int result = httpClient.POST(body);
        if (result > 0)
        {
            String resBuff = httpClient.getString();
            Serial.println("HTTP POST succssful. Response: ");
            Serial.println(resBuff);
        }
        else
        {
            Serial.println("Error sending HTTP POST request. Result code: ");
            Serial.println(httpClient.errorToString(result));
        }
    #endif
    #ifdef __SAMD21G18A__
        httpClient.post(httpEndpoint, "application/json", body);
        int statusCode = httpClient.responseStatusCode();
        if (statusCode != 200)
        {
            Serial.println("Error sending HTTP POST request:");
            Serial.println("Status code: " + String(statusCode));
        }
        else
        {
            Serial.println("HTTP POST succssful. Response: ");
        }
        Serial.print("Response: ");
        Serial.println(httpClient.responseBody());
    #endif
    
}

/**
 * @brief Sends an event using MQTT
 * 
 */
void sendEventMqtt()
{
    String jsonString = JSON.stringify(getPayloadJSON());
    Serial.println("Sending mqtt request to topic " + String(SECRET_PROJECT_NAME) + " with payload: ");
    Serial.println(jsonString);
    mqttClient.publish(SECRET_PROJECT_NAME, jsonString.c_str());
    mqttClient.endPublish();
}

bool isPressed()
{
    return digitalRead(BUTTON_PIN) == HIGH;
}

void setup()
{
    Serial.begin(115200);

    #if defined(__SAMD21G18A__)
    delay(5000);    // Delay for 5000 seconds to allow a serial connection to be established
    #endif

    initWiFi();

    if(SECRET_MQTT_ENABLED) connectToMqttBroker();

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    timeClient.begin();
}

void loop()
{
    timeClient.update();
    
    // Check we are still connected to the MQTT broker
    if(SECRET_MQTT_ENABLED) 
    {
        if (!mqttClient.connected())
        {
            Serial.println("Lost connection to the MQTT broker");
            connectToMqttBroker();
        }
        mqttClient.loop();
    }
    
    // Check if an event was triggered and send it
    if (isPressed())
    {
        Serial.println("Sending event");
        if (SECRET_MQTT_ENABLED) sendEventMqtt();
        if (SECRET_HTTP_ENABLED) sendEventHttp();
        // Wait for some time before checking the button again
        delay(3000);
    };
}

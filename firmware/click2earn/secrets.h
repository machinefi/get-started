// The ssid  and pasword for your WiFi connection
#define SECRET_WIFI_SSID        "<YOUR_WIFI_NETWORK_NAME>"
#define SECRET_WIFI_PASS        "<YOUR_WIFI_PASSWORD>"

// The hostname or ip of the w3bstream node
#define SECRET_WEBSTREAM_HOST   "<W3BSTREAM_NODE_IP>"

// The W3bstream project name
#define SECRET_PROJECT_NAME     "Click2Earn"

// The Project publisher id and token. Only used if SECRET_PUBLISHER_AUTHENTICATION_ENABLED is true
#define SECRET_PUBLISHER_ID     "001"
#define SECRET_PUBLISHER_TOKEN  "<PUB_TOKEN>"

// Advanced settings

// Set to true if you want to send events using http
#define SECRET_HTTP_ENABLED     true
// Set to true if you want to send events using mqtt
#define SECRET_MQTT_ENABLED     false

// The HTTP port of the w3bstream node. By default 8888
#define SECRET_WEBSTREAM_PORT   8888

// The MQTT port of the w3bstream node. By default 1883
#define SECRET_MQTT_BROKER_PORT 1883

// The MQTT broker hostname or ip of the w3bstream node. By default it's the same as the w3bstream node
#define SECRET_MQTT_BROKER_HOST SECRET_WEBSTREAM_HOST

// The MQTT client id. Can be set to anything
#define SECRET_MQTT_CLIENT_ID   "example_client"

// Set to true to if publisher authenticaiton is enabled in W3bstream.
#define SECRET_PUBLISHER_AUTHENTICATION_ENABLED     true


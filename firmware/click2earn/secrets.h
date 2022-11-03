// The ssid  and pasword for your WiFi connection
#define SECRET_WIFI_SSID        "<YOUR_WIFI_NETWORK_NAME>"
#define SECRET_WIFI_PASS        "<YOUR_WIFI_PASSWORD>"

// Set to true if you want to send events using http
#define SECRET_HTTP_ENABLED     true
// Set to true if you want to send events using mqtt
#define SECRET_MQTT_ENABLED     false

// The hostname or ip of the w3bstream node
#define SECRET_WEBSTREAM_HOST   "<mywebstreamhost.com>"
// The http port of the w3bstream node. By default 8888
#define SECRET_WEBSTREAM_PORT   8888

// The mqtt broker hostname or ip of the w3bstream node. By default it's the same as the w3bstream node
#define SECRET_MQTT_BROKER_HOST SECRET_WEBSTREAM_HOST
// The mqtt port of the w3bstream node. By default 1883
#define SECRET_MQTT_BROKER_PORT 1883
// The mqtt client id. Can be set to anything
#define SECRET_MQTT_CLIENT_ID   "example_client"

// If you want to enable published authenticaiton. Set to true
#define SECRET_PUBLISHER_AUTHENTICATION_ENABLED     true
// The publisher id and token. Only used if SECRET_PUBLISHER_AUTHENTICATION_ENABLED is true
#define SECRET_PUBLISHER_ID     "<PUB_ID>"
#define SECRET_PUBLISHER_TOKEN  "<PUB_TOKEN>"

// The project name
#define SECRET_PROJECT_NAME     "<W3BSTREAM_PROJECT_NAME>"

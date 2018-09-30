// WiFi Settings
const char* ssid = "WLAN-SSID";
const char* password = "WLAN Passwort";
char* espHostname = "hostame das ESP's";

// MQTT Server
const char* mqtt_server = "MQTT Broker";

// MQTT Subscribes
const char* mainTopic = "Topic/#";


// MQTT Last will and Testament
byte willQoS = 0;
const char* willTopic = "lwt/esp-topic";
const char* willOnMessage = "online";
const char* willOffMessage = "offline";
const char* willClientID = "esp-ClientID";
boolean willRetain = true;

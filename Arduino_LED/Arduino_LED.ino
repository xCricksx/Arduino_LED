// Neopixel
#include <Adafruit_NeoPixel.h>

// ESP 8266
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
extern "C" {
#include "user_interface.h" //to set the hostname
}

#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);
void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  //Neopixel start
  strip.setBrightness(brightness);
  strip.begin();
  strip.show();
  delay(50);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  wifi_station_set_hostname(espHostname); //set ESP hostname
  WiFi.mode(WIFI_STA); // set Wifi mode

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(willClientID, willTopic, willQoS, willRetain, willOffMessage)) {
      Serial.println("connected");

      // Once connected, publish an announcement...
      client.publish(willTopic, willOnMessage, willRetain);
      // ... and resubscribe
      client.subscribe(mainTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

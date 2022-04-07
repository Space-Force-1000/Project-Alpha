//
#include <Arduino.h>
#include <string>
#include "private.h"

// Important Libraries
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
String message;
void messageHandler(char* topic, byte* payload, unsigned int length);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  if ( strstr(topic, "chessBoard2/moves") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay_data = doc["move"];
    int r = Relay_data.toInt();
    Serial.println(Relay_data);
  }else if ( strstr(topic, "chessBoard1/moves") ){
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay_data = doc["move"];
    int r = Relay_data.toInt();
    Serial.println(Relay_data);
  }
}
// function for sending moves to second chessboard via aws
void myTimerEvent(String message)
{

  StaticJsonDocument<200> doc;
  doc["move"] = message;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  Serial.println("Move Published");
}

void setup() {
  Serial.begin(115200);

  connectAWS();
}

void loop() {
  if(Serial.available()){
    message = Serial.readString();
    myTimerEvent(message);
  }
  client.loop();
}
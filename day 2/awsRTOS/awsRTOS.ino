#include <ArduinoJson.h>
#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h> // change to #include <WiFi101.h> for MKR1000
#include <FreeRTOS_SAMD21.h>

#include "arduino_secrets.h"

TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;

/////// Enter your sensitive data in arduino_secrets.h
const char ssid[]        = SECRET_SSID;
const char pass[]        = SECRET_PASS;
const char broker[]      = SECRET_BROKER;
const char* certificate  = SECRET_CERTIFICATE;

WiFiClient    wifiClient;            // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection, integrates with ECC508
MqttClient    mqttClient(sslClient);

unsigned long lastMillis = 0;
String tempSaved = "" ;
bool flag = false ;

void myDelay(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );
}

static void threadA(void *pvParameters )
{
  while (1) {
    if (flag) {
      String temp = serialGet("temp") ;
      Serial.print("temp :") ;
      Serial.println(temp) ;
      tempSaved = temp ;
      myDelay(500) ;
    }
  }
}

static void threadB(void *pvParameters )
{
  while (1) {
    if (flag) {
      publishMessage() ;
      myDelay(1000) ;
    }
  }
}

StaticJsonDocument<200> doc;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600) ;
  vNopDelayMS(1000) ;
  while (!Serial);

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // Set a callback to get the current time
  // used to validate the servers certificate
  ArduinoBearSSL.onGetTime(getTime);

  xTaskCreate(threadA, "Task A", 256, NULL, tskIDLE_PRIORITY + 1, &Handle_aTask);
  xTaskCreate(threadB, "Task B", 256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);

  // Set the ECCX08 slot to use for the private key
  // and the accompanying public certificate for it
  sslClient.setEccSlot(3, certificate);

  // Set the message callback, this function is
  // called when the MQTTClient receives a message
  mqttClient.onMessage(onMessageReceived);

  vTaskStartScheduler();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    flag = false ;
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    // MQTT client is disconnected, connect
    flag = false ;
    connectMQTT();
  }

  // poll for new MQTT messages and send keep alives
  mqttClient.poll();
  flag = true ;
}

unsigned long getTime() {
  // get the current time from the WiFi module
  return WiFi.getTime();
}

void connectWiFi() {
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the network");
  Serial.println();
}

void connectMQTT() {
  Serial.print("Attempting to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connect(broker, 8883)) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the MQTT broker");
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe("arduino/incoming");
}

void publishMessage() {
  Serial.println("Publishing message");

  doc["temp"] = tempSaved ;
  String output;
  serializeJson(doc, output);
  // send message, the Print interface can be used to set the message contents
  mqttClient.beginMessage("arduino/outgoing");
  mqttClient.print(output) ;
  mqttClient.endMessage();

  Serial.print("topic : ") ;
  Serial.println("arduino/outgoing") ;
  Serial.println(output) ;
}

String serialGet(String sensor) {
  String returnMessage = "" ;
  Serial1.println(sensor) ;
  long startTime = millis() ;
  while (millis() - startTime < 500) {
    if (Serial1.available()) {
      //Serial.write(Serial1.read()) ;
      //returnMessage += (char) Serial1.read() ;
      returnMessage = Serial1.readStringUntil('\r') ;
      Serial1.readString() ;
      break ;
    }
  }
  Serial.print("serial get ") ;
  Serial.print(millis()) ;
  Serial.print(" ") ;
  Serial.println(returnMessage) ;
  return returnMessage ;
}

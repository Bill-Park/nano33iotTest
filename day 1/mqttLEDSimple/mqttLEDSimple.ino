#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.hivemq.com";
int        port     = 1883;
const char topic[]  = "arduino/0/test";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  mqttClient.onMessage(onMqttMessage);

  mqttClient.subscribe(topic);

}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();

  if (Serial.available()) {
    String readSerial = Serial.readStringUntil('\n') ;
    mqttClient.beginMessage(topic) ;
    mqttClient.print(readSerial) ;
    mqttClient.endMessage() ;
    Serial.print("Sending message to topic: ") ;
    Serial.println(topic) ;
    Serial.print("read ") ;
    Serial.println(readSerial) ;
  }
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  String fromMessage = "" ;
  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    //Serial.print((char)mqttClient.read());
    fromMessage += (char)mqttClient.read() ;
  }
  //Serial.print(fromMessage) ;
  //Serial.println();

  Serial.print("led state ") ;
  Serial.println(fromMessage) ;
  if (fromMessage == "on") {
    Serial.println("led on") ;
    digitalWrite(LED_BUILTIN, HIGH) ;
  }
  else if (fromMessage == "off") {
    Serial.println("led off") ;
    digitalWrite(LED_BUILTIN, LOW) ;
  }


  Serial.println();
}

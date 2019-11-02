#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "arduino/simple/#";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);
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
  String fromTopic = mqttClient.messageTopic() ;
  String fromMessage = "" ;
  String returnMessage = "" ;

  Serial.print("Received a message with topic '");
  Serial.print(fromTopic);
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");


  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    fromMessage += (char)mqttClient.read() ;
  }

  /////////////// get from mqtt
  if (fromTopic.substring(15, 18) == "get") {
    Serial.print("get message : ") ;
    Serial.println(fromMessage) ;
    Serial1.println(fromMessage) ;
    long startTime = millis() ;
    while (millis() - startTime < 500) {
      if (Serial1.available()) {
        //Serial.write(Serial1.read()) ;
        returnMessage += (char) Serial1.read() ;
      }
    }
    Serial.print("get message from ble : ") ;
    Serial.println(returnMessage) ;
  }
  /////////////// set from mqtt
  else if (fromTopic.substring(15, 18) == "set") {
    fromMessage.remove(1, 1) ;
    Serial.print("led") ;
    Serial.println(fromMessage) ;
    Serial1.print("led") ;
    Serial1.println(fromMessage) ;
  }

  Serial.println();
}

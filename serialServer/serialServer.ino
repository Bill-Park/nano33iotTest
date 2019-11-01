#include <Arduino_HTS221.h>
#include <Arduino_APDS9960.h>

#define SERIAL Serial1

int repeatTime = 0 ;

void setup() {
  SERIAL.begin(9600) ;
  pinMode(LEDR, OUTPUT) ;
  pinMode(LEDG, OUTPUT) ;
  pinMode(LEDB, OUTPUT) ;
  digitalWrite(LEDR, 1) ;
  digitalWrite(LEDG, 1) ;
  digitalWrite(LEDB, 1) ;

  while (!SERIAL) ;

  if (!HTS.begin()) {
    //Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!APDS.begin()) {
    //Serial.println("Error initializing APDS9960 sensor.");
  }
  while (! APDS.colorAvailable() && repeatTime < 5) {
    //SERIAL.println(".") ;
    delay(200);
    repeatTime += 1 ;
  }

  SERIAL.println("start") ;
}

void loop() {
  // put your main code here, to run repeatedly:
  String serialInput = "" ;
  if (SERIAL.available()) {
    serialInput = SERIAL.readStringUntil('\n') ;
  }
  if (serialInput == "temp") {
    float temperature = HTS.readTemperature();
    SERIAL.println(temperature) ;
  }
  else if (serialInput == "humi") {
    float humidity = HTS.readHumidity();
    SERIAL.println(humidity) ;
  }
  else if (serialInput == "light") {
    while (! APDS.colorAvailable() && repeatTime < 5) {
      delay(200);
      repeatTime += 1 ;
    }
    repeatTime = 0 ;
    int r, g, b, c;
    APDS.readColor(r, g, b, c);
    SERIAL.print(r) ;
    SERIAL.print(" ") ;
    SERIAL.print(g) ;
    SERIAL.print(" ") ;
    SERIAL.print(b) ;
    SERIAL.print(" ") ;
    SERIAL.println(c) ;
  }
  else if (serialInput.indexOf("led") == 0) {
    int ledBright = serialInput.substring(4, 7).toInt() ;
    char ledColor = serialInput.charAt(3) ;
    if (ledColor == 'r') {
      analogWrite(LEDR, ledBright) ;
    }
    else if (ledColor == 'g') {
      analogWrite(LEDG, ledBright) ;
    }
    else if (ledColor == 'b') {
      analogWrite(LEDB, ledBright) ;
    }
  }

}

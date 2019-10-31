#include <Arduino_HTS221.h>
#include <Arduino_APDS9960.h>

#define SERIAL Serial

int repeatTime = 5 ;

void setup() {
  // Start my new hardware serial
  SERIAL.begin(9600) ;
  while (!Serial) ;

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }

  SERIAL.println("start") ;
}

void loop() {
  // Do something with mySerial...
  //SERIAL.println("123") ;
  //delay(500) ;
  String serialInput = "" ;
  if (SERIAL.available()) {
    serialInput = SERIAL.readStringUntil('\n') ;
  }
  if (serialInput == "temp") {
    float temperature = HTS.readTemperature();
    SERIAL.println(temperature) ;
  }
  else if (serialInput == "humi") {
    float humidity    = HTS.readHumidity();
    SERIAL.println(humidity) ;
  }
  else if (serialInput == "light") {
    while (! APDS.colorAvailable() && repeatTime < 5) {
      //SERIAL.println(".") ;
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
}

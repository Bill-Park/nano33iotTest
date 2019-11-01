void setup() {
  // Reassign pins 5 and 6 to SERCOM alt
  //pinPeripheral(5, PIO_SERCOM_ALT);
  //pinPeripheral(6, PIO_SERCOM_ALT);

  // Start my new hardware serial
  //mySerial.begin(9600);
  Serial.begin(9600) ;
  while (!Serial) ;
  Serial1.begin(9600) ;
}

void loop() {
  // Do something with mySerial...
  if (Serial1.available()) {
    Serial.write(Serial1.read()) ;
  }
  if (Serial.available()) {
    Serial1.write(Serial.read()) ;
  }
}

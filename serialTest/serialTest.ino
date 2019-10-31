void setup() {
  // Reassign pins 5 and 6 to SERCOM alt
  //pinPeripheral(5, PIO_SERCOM_ALT);
  //pinPeripheral(6, PIO_SERCOM_ALT);

  // Start my new hardware serial
  //mySerial.begin(9600);
  Serial1.begin(9600) ;
}

void loop() {
  // Do something with mySerial...
  Serial1.println("123") ;
  delay(500) ;
}

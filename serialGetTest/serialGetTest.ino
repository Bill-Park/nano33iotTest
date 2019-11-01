void setup() {
  // Start my new hardware serial
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

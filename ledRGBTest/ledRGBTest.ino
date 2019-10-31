
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT) ;
  pinMode(LEDG, OUTPUT) ;
  pinMode(LEDB, OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDR, 0) ;
  digitalWrite(LEDG, 1) ;
  digitalWrite(LEDB, 1) ;
  delay(500) ;
  digitalWrite(LEDR, 1) ;
  digitalWrite(LEDG, 0) ;
  digitalWrite(LEDB, 1) ;
  delay(500) ;
  digitalWrite(LEDR, 1) ;
  digitalWrite(LEDG, 1) ;
  digitalWrite(LEDB, 0) ;
  delay(500) ;
  digitalWrite(LEDR, 1) ;
  digitalWrite(LEDG, 1) ;
  digitalWrite(LEDB, 1) ;
  delay(2000) ;
  
}

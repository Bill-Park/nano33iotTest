#include <FreeRTOS_SAMD21.h>

TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;

void myDelay(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );
}

static void threadA(void *pvParameters )
{
  while (1) {
    String temp = serialGet("temp") ;
    Serial.print("A :") ;
    Serial.println(temp) ;
    myDelay(500) ;
  }
}

static void threadB(void *pvParameters )
{
  while (1) {
    String light = serialGet("light") ;
    Serial.print("B :") ;
    Serial.println(light) ;
    myDelay(1000) ;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  Serial1.begin(9600) ;
  vNopDelayMS(1000) ;
  while (!Serial) ;

  Serial.println("start program") ;
  
  xTaskCreate(threadA, "Task A", 256, NULL, tskIDLE_PRIORITY + 2, &Handle_aTask);
  xTaskCreate(threadB, "Task B", 256, NULL, tskIDLE_PRIORITY + 3, &Handle_bTask);

  vTaskStartScheduler();
}

void loop() {
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

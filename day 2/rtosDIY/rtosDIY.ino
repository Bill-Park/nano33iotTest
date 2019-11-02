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
    Serial.println("Thread A start") ;
    myDelay(500) ;
  }
}

static void threadB(void *pvParameters )
{
  while (1) {
    Serial.println("Thread B start") ;
    myDelay(1000) ;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  vNopDelayMS(1000) ;
  while (!Serial) ;

  Serial.println("start program") ;
  
  xTaskCreate(threadA, "Task A", 256, NULL, tskIDLE_PRIORITY + 2, &Handle_aTask);
  xTaskCreate(threadB, "Task B", 256, NULL, tskIDLE_PRIORITY + 3, &Handle_bTask);

  vTaskStartScheduler();
}

void loop() {
}

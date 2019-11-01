#include <FreeRTOS_SAMD21.h>

TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;
SemaphoreHandle_t Handle_Sema ;

void myDelay(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );
}


void print_message(const char* name, int state)
{
  if (xSemaphoreTake(Handle_Sema, (TickType_t) 1) == pdTRUE) {
    Serial.print(name) ;
    Serial.print("  ") ;
    Serial.println(state) ;
    xSemaphoreGive(Handle_Sema) ;
  }
}


static void threadA(void *pvParameters )
{
  while (1) {
    /*
    Serial.print("Thread A start") ;
    Serial.print(pdTRUE) ;
    Serial.println(xSemaphoreTake(Handle_Sema, (TickType_t) 5)) ;
    */
    print_message("Thread A", 0) ;
    myDelay(100) ;
    print_message("Thread A", 1) ;
    myDelay(400) ;
  }
}

static void threadB(void *pvParameters )
{
  while (1) {
    print_message("Thread B", 2) ;
    myDelay(100) ;
    print_message("Thread B", 3) ;
    myDelay(400) ;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  vNopDelayMS(1000) ;
  while (!Serial) ;

  Serial.println("start program") ;
  Handle_Sema = xSemaphoreCreateMutex() ;
  
  xTaskCreate(threadA, "Task A", 256, NULL, tskIDLE_PRIORITY + 3, &Handle_aTask);
  xTaskCreate(threadB, "Task B", 256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(".") ;
  //vNopDelayMS(100);
}

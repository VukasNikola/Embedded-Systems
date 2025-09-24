#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1; 
#endif

static char str[] = "Nikola Vukas Embedded Systems!"; // String in C is just an array of chars



static TaskHandle_t task1 = NULL; // TaskHandle_t is a void pointer
static TaskHandle_t task2 = NULL;

void vPrintTask1(void *parameter)
{
  size_t string_length = strlen(str);
  while(1){
      for(int i = 0; i < string_length; i++)
  {
    Serial.print(str[i]);
    vTaskDelay(pdMS_TO_TICKS(5)); 
  }
  vTaskDelay(pdMS_TO_TICKS(1000)); 
  }
}

void vPrintTask2(void *parameter){
  for(;;){ // Can use while(1) too
    Serial.print('*');
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}


void setup()
{
  Serial.begin(300);
  vTaskDelay(pdMS_TO_TICKS(1000));
  xTaskCreatePinnedToCore(
      vPrintTask1, 
      "Print Task 1",
      1024,       
      NULL,  
      1,          
      &task1,    // Pointer to a pointer of type TaskHandle_t!!!   
      app_cpu);    


  xTaskCreatePinnedToCore(
      vPrintTask2, 
      "Print Task 2",
      1024,       
      NULL,  
      2,          
      &task2,   
      app_cpu);    

}

void loop()
{
  // Not used in simulation but shows how to pause suspend and resume task
  //   for(int i=0; i < 3; i++){
  //   vTaskSuspend(task2); // Puts the task in a suspended state
  //   vTaskDelay(pdMS_TO_TICKS(400));
  //   vTaskResume(task2); //Puts the task in the running state
  //   vTaskDelay(pdMS_TO_TICKS(400));
  // }
}


// Result: *N**ik*ol*a *Vu*ka*s *Em*be*dd*ed* S*ys*te*ms*!
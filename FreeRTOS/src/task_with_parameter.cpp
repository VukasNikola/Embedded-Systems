#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1; 
#endif

static const int led_pin = 2;
static const TickType_t delay_time = 400; // Use TickType_t this is also an integer
/**
 * Blink built in led with 500ms delay
 *
 * @param parameter void pointer
 * @return void
 */
void vBlinkTask(void *parameter)
{
  TickType_t d = *(TickType_t*)parameter;
  for(;;)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(d / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(d / portTICK_PERIOD_MS);
  }
}

void setup()
{
  pinMode(led_pin,OUTPUT);
  xTaskCreatePinnedToCore(
      vBlinkTask, 
      "Blink 400",
      1024,       
      (void*)&delay_time, // &delay_time gives the address of the TickType_t but its type is a pointer!    
      1,          
      NULL,       
      app_cpu);    

}

void loop()
{
}

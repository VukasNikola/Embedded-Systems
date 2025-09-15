#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = 2;

/**
 * Blink built in led with 500ms delay
 *
 * @param parameter void pointer
 * @return void
 */
void vBlinkTask1(void *parameter)
{
  while (1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); // Explained in doc
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
/**
 * Blink built in led with 240ms delay
 *
 * @param parameter void pointer
 * @return void
 */
void vBlinkTask2(void *parameter)
{
  while (1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(240 / portTICK_PERIOD_MS); // Explained in doc
    digitalWrite(led_pin, LOW);
    vTaskDelay(240 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  pinMode(led_pin,OUTPUT);
  xTaskCreatePinnedToCore(
      vBlinkTask1, // Task function
      "Blink 500", // Task name
      1024,        // Number of bytes in ESP32 (in vanilla it is number of words)
      NULL,        // Parameters to be given to the task function
      1,           // Priority
      NULL,        // Task handle for future reference, usually null for task which run forever, pass in address to TaskHandle_t if needed 
      app_cpu);    // Core to which the task is pinned to

  xTaskCreatePinnedToCore(
      vBlinkTask2, 
      "Blink 250", 
      1024,       
      NULL,       
      1,          
      NULL,       
      app_cpu);   
}

void loop()
{
}

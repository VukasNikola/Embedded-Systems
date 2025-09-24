#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

void vTest(void *parameter)
{
  while (1)
  {
    int a = 1;
    int b[100]; // 100 * 4 bytes = 400 bytes
    // Just a placeholder so optimizer uses the array and doesn't optimize it out
    for (int i = 0; i < 100; i++)
    {
      b[i] = a + 1;
    }
    // We just used the print below to show that the stack will overflow if the stack size is 1024 and we have an array of 100 ints
    // Serial.print(b[0]);

    Serial.print("Stack available: ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL)); // Gives you the amount of bytes left in the stack (In documentation says in bytes, video says words...)

    // With this we can see that the heap keeps shrinking because we are not freeing the malloc
    int *p = (int *)pvPortMalloc(sizeof(int)); // In vanilla FreeRTOS if we are not using heap3 scheme we want to use pvPortMalloc which is thread safe unlike regular malloc
    // You can use regular malloc in esp though...
    *p = 4;
    // NOTE: p[2] is p+2, move 2 spaces forward in memory
    if (p == NULL) // malloc returns
    {
      Serial.println("Allocation failed!");
    }
    // With the line below we free the memory in heap and so the heap available is constant
    vPortFree(p); // Thread safe free

    Serial.print("Heap size available: ");
    Serial.println(xPortGetFreeHeapSize()); // Gives total available heap in bytes
  }
}

void setup()
{
  Serial.begin(115200);
  vTaskDelay(pdMS_TO_TICKS(1000));

  xTaskCreatePinnedToCore(
      vTest,
      "Overflow Test", // We change the stack from 1024 to 1500 to have enough memory for the code
      1500,            // From the configuration document we know that 768 BYTES(SINCE WE ARE WORKING WITH ESP32 AND NOT VANILLA) is minimum, so usable is 1024-768!
      NULL,
      1,
      NULL,
      app_cpu);

  vTaskDelete(NULL); // Deletes the setup-loop task, meaning only the "Overflow Test" task will run
}

void loop()
{
}

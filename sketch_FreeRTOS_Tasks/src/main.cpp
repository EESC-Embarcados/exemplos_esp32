#include <Arduino.h>
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

int capacitiveValue;
int threshold = 20; // Limiar para ajustar

void setup()
{
  Serial.begin(115200); // Taxa de transferência serial (baud rate) = 115200 bits por segundo (bps)
  pinMode(2, OUTPUT); // Configura o pino 2 como saída

  xTaskCreate(vTask1, "TOUCH", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &taskHandle1);
  xTaskCreate(vTask2, "LED", configMINIMAL_STACK_SIZE, NULL, 1, &taskHandle2);
  // xTaskCreatePinnedToCore(vTask1, "TOUCH", 2048, NULL, 1, &taskHandle1, 1);
  // xTaskCreatePinnedToCore(vTask2, "LED", 2048, NULL, 5, &taskHandle2, 0);
} 

void loop()
{
  delay(500); // Delay de 500 ms para atualização
}

void vTask1(void *pvParameters){
  for (;;) {
    capacitiveValue = touchRead(13); 
    if (capacitiveValue < threshold) 
    {
      Serial.println("Touched");
    }
    vTaskDelay(pdMS_TO_TICKS(500)); // Adiciona um delay para evitar uso excessivo de CPU
  }
}

void vTask2(void *pvParameters){
  for (;;) {
    digitalWrite(2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(2, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

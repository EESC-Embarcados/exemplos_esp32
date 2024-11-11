// Exemplo de uso semáforos: fila de notificações, na qual uma notificação é enviada ao términio de um processamento para que o outro seja inicializado
// Usando o mesmo exemplo de duas tarefas, o semáforo notificará que a task2 estará liberada para ser executada após a execução da task1
//Bibliotecas do FreeRTOS e semaphore
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t semaphore; // Declaração de uma variável para armzenar o semáforo
// SemaphoreHandle_t é um tipo de dado definido no FreeRTOS como um ponteiro identificador de semáforo

void Task1(void * params){
    while(1){
          Serial.println("Realizando leitura de temperatura"); // exemplo de uma tarefa
          // código da tarefa aqui
          //....
         
          xSemaphoreGive(semaphore); // Libera o semáforo após a leitura
          //Serial.println("Novo processamento");
         vTaskDelay(5000 / portTICK_PERIOD_MS); // Aguarda 5s para retornar a essa tarefa


        /*
        A função vTaskDelay() é uma função do FreeRTOS que provoca delays na execução de uma tarefa, tendo como 
        argumento o valor do atraso em ticks do sistema.  
        No caso específico da linha vTaskDelay(10 / portTICK_PERIOD_MS);, o valor passado como argumento
        é 10 / portTICK_PERIOD_MS. 
        
        A constante portTICK_PERIOD_MS é definida nas bibliotecas do FreeRTOS e representa a duração de um tick do 
        sistema em milissegundos. Portanto, a função vTaskDelay(10 / portTICK_PERIOD_MS) introduz um delay de 10 ms 
       */
    }
}

void Task2(void * params){
    while(1){
        xSemaphoreTake(semaphore, portMAX_DELAY); // portMAX_DELAY aguarda a disponibilidade do semáforo para executar a próxima linha
        Serial.println("Inciando a comunicação Bluetooth"); // exemplo de uma tarefa
          // código da tarefa aqui
          //....
               
    }
}

void setup() {
    Serial.begin(115200); // taxa de comunicação serial
    semaphore = xSemaphoreCreateBinary(); // Criação do semáforo binário - incialmente uma chamada para xSemaphoreTake() bloque a tarefa até que a outra tarefa chame: xSemaphoreGive() para libera-la 

    //Configuração de prioridade, alocação de memória e seleção do core da ESP32:
    xTaskCreatePinnedToCore(Task1, "Temperatura", 2048, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(Task2, "Bluetooth", 2048, NULL, 2, NULL, 0);

  //2048: É o valor máximo da pilha (stack) alocada para cada tarefa em bytes. Determina a quantidade de memória disponível para a execução da tarefa.
  // NULL - indica que nenhum parâmetro adicional esta sendo usados para as tarefas acima (algum rótulo adicional de configuração ou ponteiro específico, que não se faz necessário aqui)
  // os numeros no quinto parametro indicam a prioridade das tarefas e os números no último parametro indicam o core da ESP32 (core0 ou core1) 
}
void loop() {
    // Não usado
}



// Exemplo de uso do FreeRTOS: trabalhando com processamento multitasking e multicore 

// FreeRTOS Permite executar várias tarefas em paralelo, maximizando a eficiência do microcontrolador, 
//compartilhamento de recursos entre tarefas, e determinismo (tarefas críticas sejam executadas em tempo hábil)


//Bibliotecas do FreeRTOS
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Tarefa 1  - alta prioridade
void Task1(void * params){  
// Função utilizada no FreeRTOS para definir uma tarefa (task) que pode ser executada em paralelo com outras tarefas no ESP32. 
  /*
    void * é um ponteiro genérico que aponta para qualquer tipo de dado. 
    params é o nome do parâmetro na função, usado para passar informações para a tarefa. 
    Por exemplo, caso precise passar dados como: 
     struct TaskParameters {
     int ledPin;
     }

     void Task1(void * params) {
       // Converte o ponteiro genérico de volta para o tipo específico
     TaskParameters *taskParams = (TaskParameters *) params;

        pinMode(taskParams->ledPin, OUTPUT);

        while (1) {
           digitalWrite(taskParams->ledPin, HIGH);
           }
  */



   // um loop infinito (while (1)) é usado para manter a tarefa em execução contínua.
    while(1){
        Serial.println("Realizando leitura de temperatura");// exemplo de uma tarefa
          // código da tarefa aqui
          //....
       
        vTaskDelay (1000 / portTICK_PERIOD_MS); // delay - aguarda 1s para retornar para essa tarefa (neste periodo o será executado a outra task)
    }
}
// Tarefa 2 - baixa prioridade

/*
No caso de duas tarefas com a mesma prioridade e o mesmo delay no FreeRTOS, o comportamento delas será determinado pelo sistema de agendamento (scheduler) do FreeRTOS.
As tarefas terão oportunidades iguais de execução e se alternam de forma justa (cada task executará por sua fatia de tempo ao chamar vTaskDelay)
*/

void Task2(void * params){
    while(1){
        Serial.println("Inciando a comunicação Bluetooth"); // exemplo de uma tarefa
          // código da tarefa aqui
          //....
        
        vTaskDelay (2000 / portTICK_PERIOD_MS);

        /*
        A função vTaskDelay() é uma função do FreeRTOS que provoca delays na execução de uma tarefa, tendo como 
        argumento o valor do atraso em ticks do sistema.  
        No caso específico da linha vTaskDelay(2000 / portTICK_PERIOD_MS);, o valor passado como argumento
        é 2000 / portTICK_PERIOD_MS. 
        
        A constante portTICK_PERIOD_MS é definida nas bibliotecas do FreeRTOS e representa a duração de um tick do 
        sistema em milissegundos. Portanto, a função vTaskDelay(2000 / portTICK_PERIOD_MS) introduz um delay de 2000 ms 
       */
    }
}

void setup() {
  Serial.begin(115200); // taxa de comunicação serial

//Configuração de prioridade, alocação de memória e seleção do core da ESP32:
 xTaskCreatePinnedToCore(Task1, "Temperatura", 2048, NULL, 5, NULL, 0);
 xTaskCreatePinnedToCore(Task2, "Bluetooth", 2048, NULL, 1, NULL, 1);

 //2048: É o valor máximo da pilha (stack) alocada para cada tarefa em bytes. Determina a quantidade de memória disponível para a execução da tarefa.
 // NULL - indica que nenhum parâmetro adicional esta sendo usados para as tarefas acima (algum rótulo adicional de configuração ou ponteiro específico, que não se faz necessário aqui)
// os numeros no quinto parametro indicam a prioridade das tarefas e os números no último parametro indicam o core da ESP32 (core0 ou core1) 
}

void loop() {
  // como é usado o processamento multitasking essa estrutura não é usada

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
Alguns conceitos de sistemas de tempo real 

Kernel de Tempo Real (Real-Time Kernel): gerencia a execução de tarefas, interrupções e sincronização em um sistema de tempo real, garantindo previsibilidade e desempenho.

Tarefas (Tasks): unidades básicas de execução em FreeRTOS, cada uma com seu próprio contexto e pilha de execução.

Deadlock: é uma situação em sistemas de computação onde dois ou mais processos ou threads ficam bloqueados indefinidamente (exclusão mútua, espera por recurso, não interrupção, espera circular).
    Exemplo: 
    P1 possui R1 e está esperando por R2.
    P2 possui R2 e está esperando por R1.
    Nenhum dos processos pode continuar, resultando em deadlock.


Round-Robin: algoritmo de escalonamento para gerenciar a execução de processos ou threads.
     Lista Circular: Todos os processos prontos são mantidos em uma fila circular.
     Quantum de Tempo: Cada processo recebe uma fatia de tempo (quantum) igual para execução. Quando o tempo de um processo expira, ele é colocado no final da fila e o próximo processo na fila é executado.
     Preempção: Se um processo não terminar durante seu quantum de tempo, ele é preemptado (interrompido) e o próximo processo é executado.

     Exemplo:

     P1 executa por 4 unidades de tempo.
     P1 é preemptado e colocado no final da fila.
     P2 executa por 4 unidades de tempo.
     P2 é preemptado e colocado no final da fila.
     P3 executa por 4 unidades de tempo.
     P3 é preemptado e colocado no final da fila.
     O ciclo recomeça com P1.

     Vantagens: justo e responsivo
     Desvantagens:overhead; não ideal para tarefas longas já que é preemptado com frequência, não dando o tempo suficiente para tarefas de longa duração em relação a outras mais rápidas

Tick Timer: temporizador que gera interrupções periódicas para permitir a multitarefa preemptiva no sistema.

Recursos do FreeRTOS:
Filas (Queues): usadas para comunicação segura e ordenada entre tarefas, permitindo o envio e recebimento de dados de forma sincronizada.

Semáforos (Semaphores): mecanismos de sincronização que controlam o acesso a recursos compartilhados ou sinalizam eventos entre tarefas.

Mutexes (Mutual Exclusion Semaphores):garantem acesso exclusivo a um recurso compartilhado, prevenindo condições de corrida entre tarefas.

Event Groups: permitem que várias tarefas esperem por múltiplos eventos, facilitando a sincronização baseada em condições complexas.

Task Notifications: sinaliza eventos diretamente entre tarefas, substituindo o uso de semáforos e filas em alguns casos.

*/
   
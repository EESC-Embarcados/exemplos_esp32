/*
-- introdução ao uso do PWM --- 
 biblioteca ledc: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html

A biblioteca ledc (LED Control) configura um sinal de PWM (Pulse Width Modulation) em um canal específico do ESP32 (por hardware). 

Configurações do programa com base na documentação da Espressif:

*/

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/ledc.h"

void pwm_init(void){
/*
  A função pwm_init() é responsável por configurar o timer e o canal LEDC para gerar o sinal PWM. Parâmetros:

  ledc_timer.speed_mode: Define o modo de velocidade do LEDC, que é configurado como LEDC_LOW_SPEED_MODE, indicando velocidade baixa.
  ledc_timer.timer_num: Especifica o número do timer LEDC que será utilizado, definido como LEDC_TIMER_0.
  ledc_timer.duty_resolution: Define a resolução do duty cycle do sinal PWM, configurada como LEDC_TIMER_13_BIT, ou seja, uma resolução de 13 bits.
  ledc_timer.freq_hz: Define a frequência do sinal PWM em hertz, ajustada para 5000 Hz.
  ledc_timer.clk_cfg: Configuração automática do clock, definida como LEDC_AUTO_CLK.
  */


ledc_timer_config_t ledc_timer;   // Declaração de uma variável do tipo ledc_timer_config_t para configurar o timer LEDC
ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;   // Define o modo de velocidade do LEDC como LEDC_LOW_SPEED_MODE
ledc_timer.timer_num  = LEDC_TIMER_0;   // Define o número do timer LEDC como LEDC_TIMER_0
ledc_timer.duty_resolution = LEDC_TIMER_13_BIT;   // Define a resolução do duty cycle como LEDC_TIMER_13_BIT (13 bits)
ledc_timer.freq_hz  = 5000;   // Define a frequência do sinal PWM em hertz como 5000 Hz
ledc_timer.clk_cfg = LEDC_AUTO_CLK;   // Configuração automática do clock

ledc_timer_config(&ledc_timer);   // Chama a função ledc_timer_config() para configurar o timer LEDC com os parâmetros definidos acima
/*
    A seguir, é feita a configuração do canal LEDC com a função ledc_channel_config():

  ledc_channel.speed_mode: Define o modo de velocidade do LEDC, que é configurado como LEDC_LOW_SPEED_MODE.
  ledc_channel.channel: Especifica o número do canal LEDC, definido como LEDC_CHANNEL_0.
  ledc_channel.timer_sel: Seleciona o timer LEDC que será utilizado, definido como LEDC_TIMER_0.
  ledc_channel.intr_type: Define o tipo de interrupção, que está desabilitado com LEDC_INTR_DISABLE.
  ledc_channel.gpio_num: Define o número do pino GPIO que será utilizado para o sinal PWM, configurado como 25.
  ledc_channel.duty: Define o valor inicial do duty cycle do sinal PWM, configurado como 0.
  ledc_channel.hpoint: Define o valor do hpoint. - 
  O hpoint (ponto de ajuste) é um dos parâmetros que define o momento em que a saída PWM (Pulse-Width Modulation) 
  será ativada ou desativada dentro do período de um ciclo PWM. No caso, está sendo definido como 0,
   o que significa que a saída PWM será ativada desde o início do ciclo.
*/


ledc_channel_config_t ledc_channel;     // Declaração da estrutura para configurar o canal LEDC
ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;    // Define o modo de velocidade como LEDC_LOW_SPEED_MODE
ledc_channel.channel = LEDC_CHANNEL_0;    // Define o número do canal como LEDC_CHANNEL_0
ledc_channel.timer_sel = LEDC_TIMER_0;    // Seleciona o timer LEDC como LEDC_TIMER_0
ledc_channel.intr_type = LEDC_INTR_DISABLE;    // Desabilita a interrupção do canal LEDC (não será usado interrupções)
ledc_channel.gpio_num = 25;    // Define o número do pino GPIO como 25 (pino que pode ser usado para controle PWM de algum periférico)
ledc_channel.duty = 0;    // Define o valor inicial do duty cycle como 0
ledc_channel.hpoint = 0;    // Define o valor de hpoint como 0
ledc_channel_config(&ledc_channel);    // Configura o canal LEDC com as opções especificadas na estrutura

}

void app_main(void)
{

  /*
  Na função app_main(), é chamada a função pwm_init() para configurar o PWM. 
  Em seguida, é executado um loop para variar o duty cycle do sinal PWM em incrementos 
  de 1 até um valor máximo de 8191 (2^13 - 1), o que corresponde a uma resolução de 13 bits. 
  A cada iteração do loop, o duty cycle é definido usando a função ledc_set_duty() com o valor atual de duty, o canal LEDC e o modo de velocidade. 
  Em seguida, a função ledc_update_duty() é chamada para atualizar o duty cycle no canal LEDC. 
  Por fim, é utilizado um pequeno atraso de 10 milissegundos usando vTaskDelay() para aguardar antes da próxima iteração do loop.

  */
   pwm_init();
   for (int duty = 0; duty < 8192; duty++){
        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
   }
}

// como é usado o FreeRTOS (tasks) as funções abaixo não são usadas (mas precisam ser declaradas no caso da Arduino IDE)
void setup(){}
void loop(){}
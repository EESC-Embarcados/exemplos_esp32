
// LED Blink - teste inicial de comunicação e controle de uma saída digital na ESP32 por meio da Arduino IDE

/* Apesar de simples, esse exemplo nos permite verificar se a comunicação entre o PC e a ESP32 esta sendo bem sucedida;
e controlar de forma safistarória uma saída digital, representada pelo LED. Além disso, é usado o próprio LED onboard (pino 2)
indicando que esta tudo ok com a placa (ESP32 Devkit).
*/
#define ledpin 32
void setup() { // configurações

pinMode(ledpin, OUTPUT); // pino 2 como saída (LED onboard da ESP32)
digitalWrite(ledpin,LOW); // escreve na saída  valor LOW (LED inicialmente desligado)

}

void loop() { // programa principal
  

digitalWrite(ledpin, HIGH);  // liga o LED (escreve valor lógio HIGH na saída - pino 2)
delay(200); // delay de 200 ms (Tempo que o LED fica ligado)
digitalWrite(ledpin, LOW); // desliga o LED (escreve valór lógico LOW na saída - pino 2)
delay(200); // delay de 200 ms (Tempo que o LED fica desligado)
// loop

}


/*
Exemplo de código na IDE Nativa ESP-IDF

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"



#define PIN 2
#define BT_PIN 34

void setup(){}

void loop ()
{
    gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(BT_PIN);
    gpio_set_direction(BT_PIN, GPIO_MODE_INPUT);

    bool status = 0;

    while(1){
        //status = !status;
        
        status = gpio_get_level(BT_PIN);
        gpio_set_level(PIN,status);
        vTaskDelay(10 / portTICK_PERIOD_MS);        
    }
}

*/
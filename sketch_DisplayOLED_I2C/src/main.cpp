// Comunicação, configuração e escrita no Display OLED via I2C

/*
Na ESP32, a comunicação serial I2C é realizada por meio dos pinos SDA (Serial Data) e SCL (Serial Clock). 
Esses pinos são responsáveis pela troca de informações entre o microcontrolador (ESP32) e os dispositivos 
conectados à mesma linha I2C.

A comunicação I2C é estabelecida pela biblioteca Wire, levando em consideração os pinos fixos SDA e SCL 
definidos no pinout da ESP32 (SDA = GPIO21; SCL = GPIO22)

A biblioteca Wire é responsável por enviar e receber os dados entre o ESP32 e o display OLED 
por meio destes pinos

O display OLED deve ser conectado fisicamente aos dois pinos acima referidos e a alimentação GND e 3V3

*/
#include <Arduino.h>
#include <Wire.h> // Biblioteca para comunicação I2C
#include <Adafruit_GFX.h> // Biblioteca para gráficos
#include <Adafruit_SSD1306.h> // Biblioteca para controle do display OLED

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/*
criam um objeto display do tipo Adafruit_SSD1306, que será usado para controlar o display OLED. 
As constantes SCREEN_WIDTH e SCREEN_HEIGHT definem a largura e altura do display, respectivamente. 
O valor -1 para OLED_RESET indica que não é necessário usar um pino específico para o reset do display. 
O objeto display é inicializado com as constantes definidas.

*/

void setup() {
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  /*

   display OLED é inicializado com display.begin(SSD1306_SWITCHCAPVCC, 0x3C), 
   onde SSD1306_SWITCHCAPVCC é uma configuração de energia do display
   0x3C é o endereço I2C do display. 
   display.clearDisplay() é usado para limpar o conteúdo atual do display, 
   e display.display() é usado para atualizar o display.

  */
}

// Cria uma variável e uma lógica de exemplo para exibir seu valor no display
int var =0;

void loop() {
  var +=1;
  if (var >255) {
    var =0;
  }

  

    display.clearDisplay();                 // Limpa o display
    display.setTextSize(1);                 // Define o tamanho do texto como 1 (pequeno)
    display.setTextColor(SSD1306_WHITE);    // Define a cor do texto como branco
    display.setCursor(0, 0);                // Define a posição do cursor para (0, 0)
    display.println("Display OLED");        // Imprime uma mensagem e muda o cursor de linha (println)
    display.print("SEL0614: ");        // Imprime uma mensagem e irá imprimir a próxima da mesma linha(print)
    display.println(var);                   // Imprime o valor de uma variável
    display.display();

    delay(500);
}
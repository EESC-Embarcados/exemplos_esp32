// Exemplo disponível na biblioteca do app Dabble na Arduino IDE 01 LedBrightnessControl com explicação adicional:

/*

A biblioteca DabbleESP32 oferece recursos para receber comandos e dados do aplicativo móvel Dabble, 
permitindo enviar dados e controlar periféricos conectados ao ESP32, como LEDs, motores e sensores de forma simplificada.

Neste exemplo (disponível na Arduino IDE - Arquivo - exemplos - DabbleEsp32 - exemplo 01):

As linhas "#define CUSTOM_SETTINGS" e "#define INCLUDE_LEDCONTROL_MODULE" são usadas para definir 
configurações personalizadas para o programa e incluir o módulo LedControl na biblioteca DabbleESP32.

 A função Dabble.begin("device_name"), chamada no setup(),inicializa a comunicação Bluetooth e 
 define o nome do dispositivo Bluetooth, conforme nome informado (ex. "MyEsp32" - pode ser qualquer outro nome).

No loop(), a função Dabble.processInput() é responsável por atualizar corretamente os dados recebidos do smartphone. 

Ao final, a função Serial.print() é usada para verificar se os parâmetros são lidos corretamente. 
No entanto, as linhas de código estão comentadas, sendo opcional. 
Caso desejar verificar as informações no monitor serial, remover os comentários dessas linhas

*/



/*
   This is Led brightness control example for ESP32 that uses LED Brightness Control Module in Dabble app.
   This module allows you to control state of pin. You can make pin HIGH or LOW or can also assign any PWM
   value to it.

   NOTE: As in esp32 any channel can be configured as a PWM channel hence any first eight pins controlled by Module
   will be treated as PWM and others will be treated as normal digital pins.
    

   You can reduce the size of library compiled by enabling only those modules that you want to
   use.For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/getting-started-with-dabble/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_LEDCONTROL_MODULE
#include <DabbleESP32.h>
unsigned long lasttime=0;
void setup() {
  Serial.begin(115200);     // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MyEsp33");     //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();    //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  //uncomment if you want to check if paramters read correctly
  /*Serial.print("Led:");
  Serial.print(LedControl.getpinNumber()); // imprime o n° do pino do LED escolhido no app Dabble
  Serial.print('\t');
  Serial.print("State:");          //0 if led is Off. 1 if led is On.
  Serial.print(LedControl.getpinState());
  Serial.print('\t');
  Serial.print("Brightness:");
  Serial.println(LedControl.readBrightness());*/
}

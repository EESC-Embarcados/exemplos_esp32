// ADC e DAC para leituras analógicas e controle de saída analógica
// Escrita em display LCD usando comunicação serial I2C

/*
ADC e DAC: o ESP32 Possui 2 x ADCs de 12 bits (4096 níveis) do tipo SAR (aprox. sucessivas) p/ leituras analógicas em 15 canais
e 2 x DACs de 8 bits (256 níveis) para controle de saídas - GPIO25 e GPIO26


O barramento I2C é composto por dois fios: 
SDA (Serial Data Line) para enviar e receber dados serializados - GPIO 21
SCL (serial clock)usado para sincronizar a transmissão de dados - GPIO 22

A utilização de bibliotecas abstrai as configurações I2C nos pinos acima.
No ESP32, geralmente os endereços do barramento I2C são destinados:

- 0x3C e 0x3D: Endereços típicos para displays OLED SSD1306.

-0x27, 0x3F, 0x38, 0x39: Endereços comuns para displays LCD baseados no chip PCF8574 ou PCF8574A.

-0x68 e 0x69: Endereços frequentemente usados por módulos de tempo real (RTC), como o DS3231.

- 0x40 a 0x4F: Endereços para expansores de E/S I2C, como o PCF8574.

- 0x50 a 0x57: Endereços para módulos de EEPROM I2C.

*/

#include <Arduino.h> // biblioteca para trabalhar com funções
// da Arduino IDE no Wokwi
#include <Wire.h>  // utilizada para a comunicação serial
#include <LiquidCrystal_I2C.h> // LCD no modo serial I2C

// Definições de pinos
const int potPin = 34;    // Pino ADC para ler o potenciômetro
const int dacPin = 25;    // Pino DAC para saída analógica

// Variáveis globais
int adcValue = 0;         // Valor lido do ADC
int dacValue = 0;         // Valor a ser escrito no DAC

// Endereço I2C do display LCD
const int lcdAddress = 0x27;
// Número de colunas e linhas do display LCD
const int lcdColumns = 16;
const int lcdRows = 2;


// Inicialização do display LCD
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);
//cria um objeto chamado lcd da classe LiquidCrystal_I2C 
//e inicializa com os parâmetros definidos anteriormente

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("ESP32 ADC to DAC Example - Iniciando");

  // Inicialização do display LCD
  lcd.init();
  lcd.backlight();

  // Configuração do pino do potenciômetro como entrada
  pinMode(potPin, INPUT);

  // Configuração do pino DAC não é necessária
  // O ESP32 cuida disso automaticamente quando usamos dacWrite()
}

 
void loop() {
  // Leitura do valor do potenciômetro (0-4095)
  adcValue = analogRead(potPin); 
  // analogRead é uma função do Arduino que realiza a leitura analógica do pino informado em potPin

  // A função Map realiza mapeamento do valor lido do ADC (0-4095) para o valor do DAC (0-255)
  dacValue = map(adcValue, 0, 4095, 0, 255);

  // Escreve o valor no DAC
  dacWrite(dacPin, dacValue); // função para escrever um valor analógico (de 0 a 255) em um dos pinos DAC 

  // Exibe os valores lidos e escritos no display LCD
  lcd.clear(); // limpa o display
  lcd.setCursor(0, 0); // seta o cursor
  lcd.print("ADC: ");  // escreve a mensagem "ADC:""
  lcd.print(adcValue); // escreve o valor lido em adcValue
  lcd.setCursor(0, 1);
  lcd.print("DAC: ");
  lcd.print(dacValue);

  // Exibe os valores lidos e escritos na porta serial (opcional)
  Serial.print("ADC Value: ");
  Serial.print(adcValue);
  Serial.print("  |  DAC Value: ");
  Serial.println(dacValue);

  //  atraso para evitar saturar a comunicação serial
  delay(100);
}


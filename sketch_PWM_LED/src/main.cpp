
// Controle do brilho de um LED por PWM usando a biblioteca ledc (vs. simplificada) na Arduino IDE

#define PIN  2
int DutyCycle = 0;

void setup() {
  // Inicializar as saídas PWM para controle do LED 
  ledcSetup(0, 5000, 8); // escolhendo o canal PWM 0, ...
  //frequência = 5000 Hz e resolução de 8 bits = divide o sinal PWM em 256 níveis (incrementos do ciclo de trabalho)
  
  ledcAttachPin(PIN, 0);   // Vincular o canal 0 ao pino do LED

}

void loop() {
  // Atualizar o duty cycle para as cores do LED
  ledcWrite(0, DutyCycle);


  //  Aumentar o duty cycle 
  DutyCycle += 5;
  if (DutyCycle > 255) {
    DutyCycle = 0;
  }

  // Aguardar um pequeno intervalo antes de atualizar o ciclo de trabalho novamente
  delay(100);
}
// Timer & interrupt no ESP32

/*
O ESP32 possui quatro timers de 0 a 3 organizados em dois grupos: Grupo 0 e Grupo 1.

Cada timer possui um divisor de clock configurável, que permite ajustar a frequência das 
interrupções geradas pelo timer

O divisor de clock divide a frequência do clock base do ESP32 para gerar a frequência do clock do timer. 

Modos de Contagem: ascendente (padrão), descendente, contagem de captura, permitindo temporização e decteção de eventos


Em relação as interrupções, o ESP32 suporta mais de 70 fontes, sendo 32 vetores de interrupção (internas e externas) em cada núcleo; 
com 25 de GPIO (externas)

*/


#include <Arduino.h>  // Inclui a biblioteca Arduino para usar suas APIs no simulador Wokwi

const int ledPin = 2;         // Define o pino do LED como GPIO2
const int buttonPin = 13;      // Define o pino do botão como GPIO4

hw_timer_t *timer = NULL;  // Declara um ponteiro para uma estrutura de timer (como NULL, por enquanto ainda
// não esta apontando para algum endereço específico)
/*
A biblioteca hw_timer_t é uma parte do ESP32 Arduino Core que permite o controle de timers 
de hardware (temporizadores) no ESP32 
A função hw_timer_t é usada para inicializar e configurar um timer, eretorna um ponteiro para 
fazer referência ao timer de hardware configurado e usado para associar interrupções 
*/
volatile bool startBlink = false;  // Variável flag para indicar o início do piscar do LED
// (volatile - pode ser alterado a qualquer tempo)


//************************************************************************************************************
// Vetor de interrupções
void IRAM_ATTR onButtonPress() {  // Função de interrupção externa de GPIO para lidar com o pressionamento do botão
  startBlink = true;  // Define a flag como verdadeira quando o botão é pressionado
}

void IRAM_ATTR onTimer() {  // Função de interrupção para lidar com o temporizador
  digitalWrite(ledPin, !digitalRead(ledPin));  // Inverte o estado do LED
}

/*
"IRAM_ATTR" é uma diretiva p/ indicar que uma função deve ser armazenada na RAM interna de instruções (IRAM)
em vez de ser armazenada na FLASH (memória de programa), necessário em situações críticas, como interrupções,
que exigem respostas rápidas

 A primeira indica que a função onButtonPress() deve ser armazenada na RAM interna, sem "()" argumentos
 A segunda indica a função "onTimer ()"


*/

//************************************************************************************************************
void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial com uma taxa de transmissão de 115200 bauds
  pinMode(ledPin, OUTPUT);  // Configura o pino do LED como saída
  pinMode(buttonPin, INPUT_PULLUP);  // Configura o pino do botão como entrada com pull-up interno


// Configuração da interrupção externa GPIO (botão)
  attachInterrupt(digitalPinToInterrupt(buttonPin), onButtonPress, FALLING);  
  // attachInterrupt (pino_evento, função de tratamento da interrupção, tipo de disparo)

  // a função "attachInterrupt" associa a função de interrupção ao pressionar botão
  // digitalPinToInterrupt(buttonPin) é o primeiro argumento da função que monitora o pino de GPIO buttonPin (n° 4)
  // onButtonPress: é o segundo argumento da função, chamado quando ocorrer o evento (tratamento)
  // FALLING - disparo da interrupção por boarda de descida

//Configuração do timer e interrupção interna associada à temporização
  timer = timerBegin(0, 80, true);  // timerBegin(timer_n°, prescaler, modo_contagem)
  //  Inicia o timer 0 com um prescaler de 80 e modo de contagem ascendente
  // considerando clock de 80 MHz:
  // f_timer =freq_clock/ porescaler
  // f_timer = 80.000.000/80 = 1 MHz = 1.000.000 ms (conta em microssegundos (1.000.000 ticks por segundo))

  timerAttachInterrupt(timer, &onTimer, true);  // Associa a função de interrupção ao timer
  /*
    "&" está passando o endereço da função onTimer para outra função, utilizada como uma rotina de tratamento de 
    interrupção associada ao timer, que será chamada neste contexto "true"
  */
  timerAlarmWrite(timer, 500000, true);  
  // Define o valor de comparação do temporizador para 500.000 microssegundos (500 ms)
}

void loop() {
  if (startBlink) {  // Verifica se startblink é verdadeiro, 
  //ou seja, se loop que irá piscar o LED foi iniciado (somente ocorrerá ao clique do botão - interrupção)

    timerAlarmEnable(timer);  // Ativa o temporizador para piscar o LED
  } else {
    timerAlarmDisable(timer);  // Desativa o temporizador caso contrário
    digitalWrite(ledPin, LOW);  // e deixa o LED desligado 
  }
}



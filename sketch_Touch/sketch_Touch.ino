/* =======================================================================
   
   Sensores Capacitivos (Touch)

   Função: touchRead(pin)
   Este exemplo serve de base para projetos que envolvem o recurso "touch" - telas touch, teclados (para digitação e musical), leitura de objetos etc.
   
   
Um sensor capacitivo touch é um dispositivo que detecta a presença ou o toque de um objeto com base
nas mudanças na capacitância. Ou seja, quando um objeto toca em uma superfície capacitiva, ocorre uma 
alteração na capacitância, e o sensor é capaz de detectar essa mudança. 

O ESP32 possui vários pinos que podem ser configurados como  touch (possuem uma camada capacitiva que pode
detectar a presença de um objeto próximo ou um toque).Pode-se ler o valor capacitivo desse pino usando a 
função touchRead(pin). Onde, pin é o n° da GPIO correspondente ao touch que se deseja usar 
(verificar pinout da ESP32 para escolha). Por exemplo, para usar o touch4 é necessário ativar
 a GPIIO 13: touchRead(13)

Essa função retorna um valor que representa a capacitância medida no pino touch. 
Esse valor pode ser comparado com um limiar pré-definido para determinar se um toque foi detectado ou não.
Ao tocar no pino, a capacitância diminui devido à alteração das propriedades dielétricas próximas ao pino 
(acoplamento capacitivo - parte da carga é transferida). Portanto, ao tocar ou se aproximar os valores 
tendem a ir para zero!
Normalmente, variações ocorrem devido ao ambiente (umidade, por ex.). A calibração geralmente é de 0 a 100. 
Mas os valores ficam em torno de 70-80 e abaixo de 20 quando ocorre o toque.


 Monitor serial (acesso em "Ferramentas > Monitor Serial") 
 O monitor serial é uma ferramenta de depuração e comunicação disponível em IDEs, que permite visualizar 
 dados transmitidos pela porta serial do dispositivo (no caso a ESP32 usa a porta serial (COM) via conexão 
 física microUSB com o PC). É necessário fazer o upload do programa para a ESP32 e que o cabo USB esteja conectado 
 para visualizar o conteúdo que foi específicado no  programa por meio das funções Serial.print e Serial.println
======================================================================= */

 
// =======================================================================
// --- Configurações Iniciais ---

int capacitiveValue;
int threshold = 20; //limiar para ajustar

void setup() 
{
  Serial.begin(115200); // taxa de transferência serial (baud rate) = 115200 bits por segundo (bps)
  pinMode(2, OUTPUT);  // pino correspondente ao LED onboard como saída
  digitalWrite(2, LOW); //  inicialmente desligado (LED apagado)
 Serial.println("ESP32 Touch Sensor Test"); // mensagem inicial impressa no monitor serial
 // A função Serial.println imprime uma mensagem ou valor no monitor serial e após isso ocorre quebra de linha
 // na função Serial.print não ocorre quebra de linha

} //end setup

// --- Loop Infinito ---
void loop() 
{
  capacitiveValue = touchRead(13); // armazena o valor lido do touch do pino13
  Serial.print("key:"); // imprimir a msg "key"...
  Serial.println(capacitiveValue); // e o valor lido no monitor serial
  delay(500); // delay de 500 ms para atualização
  
  if (touchRead(13) < threshold) {  // lógica para acender o LED onboard quando o pino13 for tocado
    digitalWrite(2, HIGH); // se sim, acende o LED (pino 2)...
    Serial.println("touched"); // msg p/ sinalizar quando houve toque
    } 
    else {
      digitalWrite(2, LOW); // caso contrário, o LED permanece apagado
      }

} //end loop


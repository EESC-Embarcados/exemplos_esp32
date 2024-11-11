



#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// As bibliotecas freertos/FreeRTOS.h e freertos/task.h são usadas para o sistema operacional de tempo real FreeRTOS, 
//que pode ser usado para agendar tarefas no ESP32.


#include <ESP32Servo.h> // biblioteca  específica para o controle de servos no ESP32

Servo servoMotor; // É criado um objeto da classe Servo chamado servoMotor, o qual será usado para controlar o servo motor.

int angle = 0;      //  angulo atual do servo
int increment = 15;  // Incremento para o movimento do servo


void setup() {
  servoMotor.setPeriodHertz(50);  // Define a frequência do servo para 50Hz
  servoMotor.attach(4, 500, 2500);  // Conecta o servo ao pino 4 com pulsos de 500us a 2500us
 //o servo espera receber um sinal PWM com uma frequência de 50Hz. 
 //A função servoMotor.attach(4, 500, 2500) conecta o servo ao pino GPIO 4 e especifica os pulsos de largura
 // para controlar a posição do servo, sendo 500 microssegundos para a posição mínima e 2500 microssegundos para a posição máxima.
  
}

// controlar o servo em loop
void loop () {
// o ângulo do servo é definido usando servoMotor.write(angle), 
//o que move o servo para a posição correspondente ao ângulo atual. 
//Em seguida, o ângulo é incrementado com angle += increment. 
//Se o ângulo atingir 180° ou 0°, o sentido do movimento é invertido multiplicando o valor de increment

    servoMotor.write(angle);
    // Atualiza o ângulo do servo
    angle += increment;

    // Verifica se o ângulo chegou a 90°
    if (angle >= 90) {
      angle =0;
    }

    // Aguarda um delay antes de atualizar o ângulo
    delay(500);
}





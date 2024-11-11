
// Exemplo 02  disponível da Arduino IDE (Arquivo - exemplos - DabbleEsp32 - 02 -Terminal) com comentários adicionais:
/*
   Terminal Module is like a chat box. It allows you to send and receive commands between your
   board and smartphone.

   You can reduce the size of library compiled by enabling only those modules that you
   want to use. For this first define CUSTOM_SETTINGS followed by defining
   INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/terminal-module/

   1 - Inclusão de bibliotecas e definição de configurações:
*/

// As linhas "#define CUSTOM_SETTINGS" e "#define INCLUDE_TERMINAL_MODULE" são usadas para definir configurações para o programa e incluir módulo Terminal na biblioteca DabbleESP32.
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>
String Serialdata = "";
bool dataflag = 0;
void setup() {

//A linha "Serial.begin(115200);" configura a comunicação serial com uma taxa de transmissão de dados de 115200 bits por segundo.
//A linha "Dabble.begin("MyEsp32");" inicia a biblioteca DabbleESP32 e define o nome do dispositivo Bluetooth como "MyEsp32".

  Serial.begin(115200);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("professor");    //set bluetooth name of your device
}

void loop() {
//A linha "Dabble.processInput();" é usada para atualizar os dados obtidos do smartphone.
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  while (Serial.available() != 0)
  /*
  A estrutura "while (Serial.available() != 0)" verifica se há dados disponíveis para leitura na porta serial.
  Se houver dados disponíveis, eles são lidos e concatenados na variável "Serialdata" até que nenhum dado esteja mais disponível.
  A variável "dataflag" é definida como 1 para indicar que dados foram recebidos.

  */
  {
    Serialdata = String(Serialdata + char(Serial.read()));
    dataflag = 1;
  }
  if (dataflag == 1)
  {
    //Impressão dos dados recebidos no Terminal: Se "dataflag" for igual a 1, isso significa que foram recebidos dados da porta serial.
    //A função "Terminal.print(Serialdata);" imprime os dados recebidos no Terminal
    Terminal.print(Serialdata);
    Serialdata = "";
    dataflag = 0;
  }
  if (Terminal.available() != 0)
  {

    /*
    Envio de dados do Terminal para a porta serial: A estrutura "if (Terminal.available() != 0)" verifica se há dados disponíveis para leitura no Terminal.
    Se houver dados disponíveis, eles são lidos e enviados para a porta serial usando a função "Serial.write(Terminal.read())".
    Em seguida, uma nova linha é enviada usando "Serial.println()".

    */
    while (Terminal.available() != 0)
    {
      Serial.write(Terminal.read());
    }
    Serial.println();

    /* caso desejar realizar outra função ao digitar o valor no terminal do app Dabble a partir deste exemplo, usar algo como a estrutura abaixo, substituindo o trecho acima
    dentro do bloco "if"
    
    String command = Terminal.readString(); // Ler o comando enviado pelo terminal

    incremento = command.toInt(); // Converter o comando para um valor inteiro
    
      Terminal.print("Increment applied: "); //retorna a mensagem para o terminal
      Terminal.println(incremento);

    */
  }
}

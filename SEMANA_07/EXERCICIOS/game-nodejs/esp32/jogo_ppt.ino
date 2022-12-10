#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>   //biblioteca para usar a hora como seed random  

#define btnP1 37    //Botão que inputa ação do player 1
#define btnP2 17   //Botão que inputa ação do player 2
#define ledP1 39   //Led que mostra vitória do player 1
#define ledP2 12   //Led que mostra vitória do player 2

int opt[3] = {0,1,2};  //Numeros que representam as opções
                      //0=pedra; 1=papel; 2=tesoura 
int opt1 = 0;         //opção escolhida pelo p1
int opt2 = 0;         //opção escolhida pelo p2

int result[2][1] = {{0},{0}}; //vetor que armazena as jogadas
                              //correspondentes de cada jogador
String win = "";

//-------------Conexão com o servidor-------
const char* SSIDS[4]={"Redmi 9","Inteli-COLLEGE"};
const char* PWD[4]={"12345678","QazWsx@123"};

int parar=0;

//Função para conectar em APs sem medição FTM
void Conectar(int rede)
{
  Serial.println("Conectando na rede: ");
  Serial.println(rede);
  WiFi.begin(SSIDS[rede],PWD[rede]);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
      while(parar==0)
      {
        Serial.println("WiFi connected");
        //DadosConexao();
        postDataToServer(win);      
        parar = menu2();
      }
      parar=0;
      WiFi.disconnect();
      Serial.println("Desconectei!");
}

void postDataToServer(String resultado) {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://c0n21h-3081.preview.csb.app/led1");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<256> doc;
    // Add values in the document
    //
    doc["Win"] = resultado;
   
    // Add an array.
    //
    JsonArray data = doc.createNestedArray("data");
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
    else {
     
      //Serial.printf("Error occurred while sending HTTP POST: %s\n", httpClient.errorToString(statusCode).c_str());
       
    }
     
}

int menu()
{
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("0 - Scan de redes"));
  Serial.println(F("1 - Conectar no beacon 1\n"));
  Serial.println(F("2 - Conectar no beacon 2\n"));
  Serial.println(F("3 - Conectar no beacon 3\n"));
  Serial.println(F("4 - Conectar nos 3 beacons (sequencialmente) \n"));
  Serial.println(F("5 - Conectar no WIFI e enviar dados para o servidor.  \n"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}

int menu2()
{
  Serial.println(F("\nEscolha uma opção 2:"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}

//----------Logica do jogo


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  pinMode(btnP1, INPUT_PULLUP);
  pinMode(btnP2, INPUT_PULLUP);
  pinMode(ledP1, OUTPUT);
  pinMode(ledP1, OUTPUT);
  srand(micros());
  Serial.println(digitalRead(btnP1));
  Serial.println(digitalRead(btnP2));
  Serial.println(micros());
}

void loop() {
//  int opcao = menu();
//  switch(opcao)
//  {
//    case 5:
//      Serial.println("Conectar na internet e enviar dados para o servidor!");
//      Conectar(0);
//      break;
//    default:
//      Serial.println("Opção fora do padrão!");
//      break;
//  }


  while ((opt1 == 0) || (opt2 == 0)){

    if(!digitalRead(btnP1)){
      opt1 = rand() % 3 + 1;  //retorna um numero entre 1 e 3
      result[0][0] = opt1;
      Serial.println("Opção:" + result[0][0]);
      //debounce
      delay(500);
      switch(opt1){
        case 1:
          Serial.println("Jogador 1 escolheu Pedra!" + result[0][0]);
          digitalWrite(ledP1, HIGH);
          break;
        case 2:
          Serial.println("Jogador 1 escolheu Papel!");
          digitalWrite(ledP1, HIGH);
          break;
        case 3:
          Serial.println("Jogador 1 escolheu Tesoura!");
          digitalWrite(ledP1, HIGH);
          break;
        default:
          Serial.println("Nenhuma opção válida escolhida");
          break;
      }
    }
    if(!digitalRead(btnP2)){
      opt2 = rand() % 3 + 1;  //retorna um numero entre 1 e 3
      result[1][0] = opt2;
      Serial.println("Opção:" + result[1][0]);
      delay(500);
      switch(opt2){
        case 1:
          Serial.println("Jogador 2 escolheu Pedra!");
          digitalWrite(ledP1, HIGH);
          break;
        case 2:
          Serial.println("Jogador 2 escolheu Papel!");
          digitalWrite(ledP1, HIGH);
          break;
        case 3:
          Serial.println("Jogador 2 escolheu Tesoura!");
          digitalWrite(ledP1, HIGH);
          break;
        default:
          Serial.println("Nenhuma opção válida escolhida");
          break;
      }
    }
  }
  Serial.println(result[0][0]);
  Serial.println(result[1][0]);
  delay(2000);
  switch(opt1){
    case 1:
      if (result[1][0] == 1){
        win = "Empate!";
      } else if (result[1][0] == 2) {
         win = "Vitória do Jogador 2!!";
        } else {
          win = "Vitória do Jogador 1!!";
        }
      break;
    case 2:
      if (result[1][0] == 1){
        win = "Vitória do Jogador 1!";
      } else if (result[1][0] == 2) {
         win = "Empate!!";
        } else {
          win = "Vitória do Jogador 2!!";
        }
      break;
    case 3:
      if (result[1][0] == 1){
        win = "Vitória do Jogador 2!";
      } else if (result[1][0] == 2) {
         win = "Vitória do Jogador 1!!";
        } else {
          win = "Empate!!";
        }
      break;
  }

  Serial.println(win);
  Conectar(0);
  delay(10000);
}

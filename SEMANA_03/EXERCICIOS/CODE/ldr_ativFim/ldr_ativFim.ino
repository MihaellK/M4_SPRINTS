
int ledList[4] = {38,39,40,41};
int ledBitList[4] = {0,0,0,0};
int buzzer = 6;
int btn1 = 35;
int btn2 = 36;
int readLight = LOW;
int play = LOW;
int ldr = 4;
//Valores min e max para o ldr, usados na conversão para binario
int ldrMinValue = 64;
int ldrMaxValue = 3640;
//Valro do ldr e sua conversão
int ldrValue = 0;
float ldrValueConvert = 0;
float tom = 0;
//Array de armazenamento dos valores a serem tocados
int sequencia[4] = {0,0,0,0};
//Variavel para contar numero de leituras gravadas
int count = 0;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i<4; i++){
  pinMode(ledList[i], OUTPUT);
  }
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  Serial.println("estou aqui!");
  //Ao pressionar o botao
  if (digitalRead(btn1) == LOW){
    //Lê LDR e converter valor para binario
    ldrValue = analogRead(ldr);
    ldrValueConvert = ((ldrMaxValue - ldrMinValue)/16);
    ldrValue = (int)ldrValue/ldrValueConvert;

    sequencia[count] += ldrValue;
    count = count + 1;

    //Muda os valores do led correspondente na lista a depender do valor pós convertido
    //e seta o tom para cada valor
    switch(ldrValue) {
      case 1:
        ledBitList[0] = 0;
        ledBitList[1] = 0;
        ledBitList[2] = 0;
        ledBitList[3] = 0;
        tom = 261.63;
        break;
      case 2:
        ledBitList[0] = 0;
        ledBitList[1] = 0;
        ledBitList[2] = 0;
        ledBitList[3] = 1;    
        tom = 293.66;    
        break;
      case 3:
        ledBitList[0] = 0;
        ledBitList[1] = 0;
        ledBitList[2] = 1;
        ledBitList[3] = 0;
        tom = 329.63;
        break;
      case 4:
        ledBitList[0] = 0;
        ledBitList[1] = 0;
        ledBitList[2] = 1;
        ledBitList[3] = 1;
        tom = 349.23;
        break;
      case 5:
        ledBitList[0] = 0;
        ledBitList[1] = 1;
        ledBitList[2] = 0;
        ledBitList[3] = 0;
        tom = 392.00;
        break;
      case 6:
        ledBitList[0] = 0;
        ledBitList[1] = 1;
        ledBitList[2] = 0;
        ledBitList[3] = 1;
        tom = 440.00;
        break;
      case 7:
        ledBitList[0] = 0;
        ledBitList[1] = 1;
        ledBitList[2] = 1;
        ledBitList[3] = 0;
        tom = 466.16;
       break;
      case 8:
        ledBitList[0] = 0;
        ledBitList[1] = 1;
        ledBitList[2] = 1;
        ledBitList[3] = 1;
        tom = 493.88;
        break;
      case 9:
        ledBitList[0] = 1;
        ledBitList[1] = 0;
        ledBitList[2] = 0;
        ledBitList[3] = 0;
        tom = 523.25;
        break;
      case 10:
        ledBitList[0] = 1;
        ledBitList[1] = 0;
        ledBitList[2] = 0;
        ledBitList[3] = 1;
        tom = 587.33;
        break;
      case 11:
        ledBitList[0] = 1;
        ledBitList[1] = 0;
        ledBitList[2] = 1;
        ledBitList[3] = 0;
        tom = 659.25;
        break;
      case 12:
        ledBitList[0] = 1;
        ledBitList[1] = 0;
        ledBitList[2] = 1;
        ledBitList[3] = 1;
        tom = 698.46;
        break;
      case 13:
        ledBitList[0] = 1;
        ledBitList[1] = 1;
        ledBitList[2] = 0;
        ledBitList[3] = 0;
        tom = 783.99;
        break;
      case 14:
        ledBitList[0] = 1;
        ledBitList[1] = 1;
        ledBitList[2] = 0;
        ledBitList[3] = 1;
        tom = 880.00;
        break;
      case 15:
        ledBitList[0] = 1;
        ledBitList[1] = 1;
        ledBitList[2] = 1;
        ledBitList[3] = 0;
        tom = 987.77;
        break;
      case 16:
        ledBitList[0] = 1;
        ledBitList[1] = 1;
        ledBitList[2] = 1;
        ledBitList[3] = 1;
        tom = 1046.50;
        break;
    }
    
    for (int i = 0; i<4; i++){
      if (digitalRead(ledBitList[i]) == 0){
        digitalWrite(ledList[i],HIGH);
      } else{
        digitalWrite(ledList[i],LOW);
        }
      }
    //debounce
    tone(buzzer,tom, 200);
    delay(1500);  
  }
  
  if (digitalRead(btn2) == LOW){
    for (int i = 0; i<4; i++){
      ldrValue = sequencia[i];
      if (digitalRead(ledBitList[i]) == 0){
        digitalWrite(ledList[i], HIGH); 
      }
      tone(buzzer,tom, 200);
      delay(1000);
     }
    count = 0;
  }

 
  

}

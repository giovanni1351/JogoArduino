#include <LiquidCrystal.h>

int seconds = 0;
volatile bool resetarVer = false;
LiquidCrystal lcd_1(13, 12, 11, 10, 8, 7);
int verdade = 3;
int mentira = 4;
int resetar = 4;
int ledVermelho = 5;
int ledVerde = 6;
int buzzer = 9;
int aleatorio[4][6]={
  {1,1,2,2,1,1},
  {1,2,1,1,1,2},
  {2,1,2,2,2,1},
  {1,1,2,2,2,2},  
};
int estado = 0;
void tocarMusicaDeEspera(){
	
}
void AcenderledVermelho(){
	digitalWrite(ledVermelho,HIGH);
  	tone(buzzer,262);
  	delay(300);
    noTone(buzzer);
  	delay(700);
  	digitalWrite(ledVermelho,LOW);
}
void AcenderledVerde(){
	digitalWrite(ledVerde,HIGH);
  	tone(buzzer,330);
  	delay(300);
    noTone(buzzer);
  	delay(700);
  	digitalWrite(ledVerde,LOW);
}

void nao(){
  if(estado == 0){
  	estado = 1;
  }
  else if(estado == 1){
  	AcenderledVermelho();
  }
        
}
void sim(){
  if(estado == 0){
  	estado = 1;
  }
  else if(estado == 1){
  	AcenderledVerde();
  }
        
}
void resetou(){
    estado = 0;
  	resetar = true;
}

int lerEntrada(){
	int clicouSim = !digitalRead(verdade);
  	int clicouNao = !digitalRead(mentira);
  if(clicouSim)return 1;
  if(clicouNao)return 2;
  return 0;
}


void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
  pinMode(buzzer, OUTPUT);
  pinMode(verdade,INPUT_PULLUP);
  pinMode(mentira,INPUT_PULLUP);
  pinMode(resetar,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(resetar), resetou, FALLING);
  
  // Print a message to the LCD.
  Serial.begin(9600);
}
int jogada = 0;
int ponteiroVerJogada=0;
void loop()
{
	
  if(estado == 0){
    lcd_1.setCursor(0, 0);
  	lcd_1.print("Jogo Sabedoria");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Sim para comecar");
    if(lerEntrada()==1){
      tocarMusicaDeEspera();
      estado=1;
    }

  }else if(estado == 1){
  	lcd_1.setCursor(0, 0);
  	lcd_1.print("Jogo da memoria");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Memorize a Sequencia");
    for(int x = 0 ;x < 6; x++){
      if(!resetarVer){
          if(aleatorio[jogada%4][x]-1){
            AcenderledVermelho();
          }else{
            AcenderledVerde();
          }
      }
    }
   	estado == 2; 
  }else if(estado == 2){
    int jogadaAtual = 0;
    int entradaDaJogada= lerEntrada();
  	if(entradaDaJogada) jogadaAtual=entradaDaJogada;
    if(aleatorio[jogada%4][ponteiroVerJogada]==jogadaAtual){
      ponteiroVerJogada++;
    }
  }
  //lcd_1.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd_1.print(seconds);
  delay(1000); // Wait for 1000 millisecond(s)
  //seconds += 1;
}



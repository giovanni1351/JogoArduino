#include <LiquidCrystal.h>

volatile bool resetarVer = false;
LiquidCrystal lcd_1(13, 12, 11, 10, 8, 7);
unsigned short resetar = 2, verdade = 3, mentira = 4, ledVermelho = 5, ledVerde = 6, buzzer = 9;
unsigned short jogada = 0, ponteiroVerJogada = 0, estado = 0;
short aleatorio[4][6] = {
    {1, 1, 2, 2, 1, 1},
    {1, 2, 1, 1, 1, 2},
    {2, 1, 2, 2, 2, 1},
    {1, 1, 2, 2, 2, 2},
};
char * perguntas[] = {"Sexta tem feira?","Um float tem 64 bits?","Tem classe em C?"};
short respostasPergunta[] = {1,2,2};

void tocarMusicaDeEspera()
{
}
void tocarEscolha(int entradaDaJogada)
{
    if (entradaDaJogada == 2)
    {
        AcenderledVermelho();
    }
    else if (entradaDaJogada == 1)
    {
        AcenderledVerde();
    }
};
void AcenderledVermelho()
{
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 262);
    delay(300);
    noTone(buzzer);
    delay(700);
    digitalWrite(ledVermelho, LOW);
}
void AcenderledVerde()
{
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 330);
    delay(300);
    noTone(buzzer);
    delay(700);
    digitalWrite(ledVerde, LOW);
}

void resetou()
{
    estado = 0;
    resetarVer = true;
}
void printarLongo(char *texto, int caracteres)
{
    lcd_1.clear();
    lcd_1.begin(16, 2);
    lcd_1.print(texto);
    delay(2000);
    for (int positionCounter = 0; positionCounter < caracteres; positionCounter++)
    {
        lcd_1.scrollDisplayLeft();
        delay(150);
    }
}
void printar(char *texto, int caracteres, int lugar)
{
    lcd_1.clear();
    lcd_1.setCursor(0, lugar);
    lcd_1.print(texto);
    for (int positionCounter = 0; positionCounter < caracteres; positionCounter++)
    {
        // scroll one position left:
        lcd_1.scrollDisplayLeft();
        // wait a bit:
        delay(150);
    }
}
void PrintarDuasLinhas(char *textoCima,char *textoBaixo,int Timerdelay){
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(textoCima);
    lcd_1.setCursor(0, 1);
    lcd_1.print(textoBaixo);
    delay(Timerdelay);
}

void respondeuIncorreto()
{
    PrintarDuasLinhas("","Incorreto",2000);
    PrintarDuasLinhas("","Voltando ao inicio",1);
    estado = 0;
    ponteiroVerJogada = 0;
}

int lerEntrada()
{
    while (true)
    {
        int clicouSim = !digitalRead(verdade);
        int clicouNao = !digitalRead(mentira);
        int clicouReset = !digitalRead(resetar);
        if (clicouSim)
            return 1;
        if (clicouNao)
            return 2;
        // if (clicouReset)
        // {
        //     estado = 0;
        //     return 0;
        // }
    }
}
int lerEntradaPergunta()
{
    int timer = 1000;
    while (timer>0)
    {
        int clicouSim = !digitalRead(verdade);
        int clicouNao = !digitalRead(mentira);
        int clicouReset = !digitalRead(resetar);
        if (clicouSim)
            return 1;
        if (clicouNao)
            return 2;
        // if (clicouReset)
        // {
        //     estado = 0;
        //     return 0;
        // }
        delay(1);
        timer--;
    }
    return -1;
}
int perguntarParaJogador(char* pergunta,int respostaCorreta,int x){
    
        char timer[30],numeroDaQuestao[30];
        printarLongo(pergunta,10);
        for(int y = 10 ; y> 0;y--){
            sprintf(timer,"  TIMER %d",y);
            sprintf(numeroDaQuestao,"Questao %d de 5",x);
            PrintarDuasLinhas(timer,"  SIM  OU  NAO",0);
            int resposta = lerEntradaPergunta();
            if(resposta == 1)PrintarDuasLinhas(timer," *SIM  OU  NAO",2000);
            if(resposta == 2)PrintarDuasLinhas(timer,"  SIM  OU *NAO",2000);
            if(resposta == respostaCorreta){
                PrintarDuasLinhas("Parabens acertou!",(char *)numeroDaQuestao,2000);
                return 1;
            }else if(resposta != respostaCorreta && resposta != -1){
                PrintarDuasLinhas("Voce errou !","Voltando ao inicio",2000);
                return 0;
            }
        } 
    return 0;
}



void setup()
{

    lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
    pinMode(buzzer, OUTPUT);
    pinMode(verdade, INPUT_PULLUP);
    pinMode(mentira, INPUT_PULLUP);
    pinMode(resetar, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(resetar), resetou, FALLING);

    // Print a message to the LCD.
    Serial.begin(9600);
}

void loop()
{
    Serial.println(estado);
    if (estado == 0)
    {
        resetarVer = false;
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Jogo Sabedoria");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Sim para comecar");
        if (lerEntrada() == 1)
        {
            tocarMusicaDeEspera();
            estado = 4;
        }
    }
    else if (estado == 1)
    {
        printarLongo("Jogo da memoria", 4);
        delay(1000);
        // lcd_1.setCursor(0, 0);
        // lcd_1.print("Jogo da memoria");
        // lcd_1.setCursor(0, 1);
        printar("Memorize a Sequencia", 4, 1);
        // lcd_1.print("Memorize a Sequencia");
        for (int x = 0; x < 6; x++)
        {
            if (!resetarVer)
            {
                if (aleatorio[jogada % 4][x] - 1)
                {
                    AcenderledVermelho();
                }
                else
                {
                    AcenderledVerde();
                }
            }
            else
            {
                estado = 0;
                break;
            }
        }
        if (!resetarVer)
            estado = 2;
    }
    else if (estado == 2)
    {
        PrintarDuasLinhas("Clique em sequencia","",1000);
        if (resetarVer){estado = 0;return;}
        int jogadaAtual = 0;
        int entradaDaJogada = lerEntrada();
        tocarEscolha(entradaDaJogada);
        if (entradaDaJogada)jogadaAtual = entradaDaJogada;
        else{estado = 0;resetarVer = 1;}
        if (aleatorio[jogada % 4][ponteiroVerJogada] == jogadaAtual){
            ponteiroVerJogada++;
            PrintarDuasLinhas("","Correto",0);
        }
        else respondeuIncorreto();
        if (ponteiroVerJogada == 6)estado = 3;
    }
    else if (estado == 3)
    {

        PrintarDuasLinhas("Parabens, voce","acertou a sequencia",3000);
        //printarLongo("Parabens voce acertou a sequencia", 20);
        estado = 4;
    }
    else if (estado == 4)
    {
        PrintarDuasLinhas("Fase de perguntas","",1000);
        PrintarDuasLinhas("Responda com","Sim ou nao",2000);
        estado = 5;
    }else if(estado == 5)
    {
        for(short x = 0 ; x <3;x++){
            perguntarParaJogador(perguntas[x],respostasPergunta[x],x);
        }
        
    }
    // lcd_1.setCursor(0, 1);
    //  print the number of seconds since reset:
    // lcd_1.print(seconds);
    //delay(1000); // Wait for 1000 millisecond(s)
                 // seconds += 1;
}

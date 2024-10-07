# JogoArduino
![image](https://github.com/user-attachments/assets/e3e3f16a-c050-4626-8d8f-068eaf153692)


https://github.com/user-attachments/assets/ed05b06e-f933-4678-8756-ebbf0adab31e



## Jogo para arduino de quiz

### o jogo tem 3 etapas:

- Jogo da memória
- Jogo do quiz
- Pergunta final

### Jogo da memória

O jogo da memória funciona da seguinte maneira:
#### Etapa de memorização:
É sorteado uma sequencia, essa sequencia consistem em vermelho e verde (representado por leds), cada um com um som correspondente, ou seja, quando acender respectiva situação, o led acende e o som é ativado (um som para cada tipo de cor).

#### Etapa de mostrar sua memória

Após decorar a sequencia de leds, voce precisa clickar nos botões correspondentes na mesma sequencia que foi mostrada, caso voce erre, o jogo se reinicia

### Quiz 

A segunda etapa do jogo é o quiz, que funciona da seguinta forma:

#### Pergunta

a pergunta que é armazenada em um banco de questões, atualmente com 15, é sorteada 5, de maneira 100% aleatória, e com verificadores de duplicidade, ou seja, toda jogada é uma jogada diferente, voce sempre vai ver uma sequencia nova. A pergunta vai ser mostrada a partir do display de uma forma de display corrido, logo depois começa a parte de reponder a pergunta 

#### Resposta

Apos a pergunta ser mostrada na tela, o usuario tem 10 segundos para responder, podendo responder com sim ou não. Na tela vai ser mostrada em qual pergunta o jogador está, e quanto tempo falta, mostrada por um cronometro. Caso a pergunta não seja respondida no tempo do cronometro, a pergunta é valida como errado, tirando uma de duas chances para o jogador. Caso a resposta seja correta o jogador passa para a proxima pergunta, assim tendo que testar novamente seu conhecimento até a etapa final.

### Pergunta final

Está etapa (a pergunta final), é a etapa na qual tem como o objetivo ser a mais desafiadora do jogo, caso o jogador erre, ele vai para o começo, e caso ele acerte, ele recebe uma incrivel recompensa, (um elogio e uma musica de vitoria)


-----------------------------------

# Funcionamento do código

## Declaração de variaveis

Inicialmente criei as variaveis globais, que serão utilizadas pelo código no decorrer de seu funcionamendo

### Variavel para o estado
com a variavel `int estado = 0` sendo a mais importante para o funcionamento, sendo ela a responsavel para separar cada momento do jogo, `estado = 0` para quando o jogo está em espera, `estado = 1` para mostrar a sequencia, `estado = 2` para receber a sequencia que o jogador vai clickar, caso sucesso a variavel estado é incrementada e passa a valer 3, no `estado = 3` ele vai mostrar na tela Parabens e vai para o `estado = 4`, no qual vai printar no lcd que estamos começando a fase de perguntas, indo para o `estado = 5`, temos um for que vai percorrer a array de perguntas sorteadas (sorteada no estado 0), chamando então a função de perguntar e receber a resposta, no `estado = 6`, caso o jogador passe de fase, terá a pergunta final, e tambem o show das respostas

### Array das Perguntas

Criei um banco de perguntas em uma array `char * perguntas[] = {
'pergunta 1','pergunta 2'
};`
### Array das respostas das perguntas

Para cada pergunta ela tem sua resposta, sem 1 para sim e 2 para não
`short respostasPergunta[] = {1,2};`
Essa array que tem como objetivo armazenar as resposta tem que ter o mesmo tamanho da array de perguntas, sendo 1 para 1, o código vai acessar por um ponteiro que está armazenada da array do sorteio das perguntas, ou seja, temo junto uma array `int perguntasEscolhidas[5];` que inicialmente não tem valor definido, sendo assim, definida no decorrer do código pela função chamada `voidgerarSequencia(int quantidadeDeQuestao)`, recebendo o total de questões no banco de questões(`char * perguntas[];`)

### Variaveis de controle de sub-estados

temos algumas variaveis que vão ser utilizadas no decorrer do código para ajudar no funcionamento do código, sendo criadas globalmente como `bool resetarVer`,`int ponteiroVerJogada`,`int jogada`

-----------

## Funcionalidades

### Prints/ Outputs

Temos 3 funçoes para mostrar texto no LCD, 2 funções para o LED e uma função para o Buzzer

#### Prints no lcd
Função para printar um texto que será mostrado de forma de scroll
`void printarLongo(char *texto, int caracteres)`
Função simples para printar uma linha apenas
`void printar(char *texto, int caracteres, int lugar)`
E uma função para mostrar na tela de lcd duas linhas 
`void PrintarDuasLinhas(char *textoCima,char *textoBaixo,int TimerdelayMeu)`
#### Acender o LED
Nestas funções, cada uma respectivamente acende um led de sua respectiva cor, por um determinado tempo,(ela alem disso faz um som com o buzzer, diferentes entre si)
`void AcenderledVermelho()`
`void AcenderledVerde()`
ela é utilizada em varios momentos do código, quando vc clicka em um botão, no jogo da memória e quando a sequencia é mostrada

#### Tocar musica

`void tocarMusicaDeEspera()`
Função utilizada no inicio do jogo, quando é clickado o botão para se iniciar, e quando o jogador vence

### Entradas/Inputs

Foi escolhido para esse jogo, o input do botão funcionar em funções, enquanto a função está em execução o programa está lendo o input do jogador

#### Meu próprio delay

Um dos maiores problemas que enfrentei foi para ler o botão de resetar enquanto estava no delay, por isso criei um delay que a cada 1 milisegundo ele vai testar o input, para assim não ter o problema do código realmente estar parado, por conta disso todos os delays do jogo é um `void delayMeu(int tempo)`

#### Ler entrada

temos duas funções,`int lerEntrada()` e `int lerEntradaPergunta()`, tendo um funcionamento parecido, porem uma lendo até o jogador realmente digitar algo, e a outra que vai ler apenas por 1 segundo.
A função `int lerEntrada()` é utilizada para o inicio do jogo e para ler a sequencia memorizada pelo jogador, tendo em vista que ele pode levar o tempo que for para dizer o que foi memorizado. Ja a função  `int lerEntradaPergunta()` é utilizada apenas na entrada da resposta da pergunta, tendo em vista que temos um tempo determinado para responder, a função é chamada dentro de um loop junto de um contador de segundo, servindo para contar o tempo restante que o jogador tem para digitar sua resposta.
Na função de perguntar ao jogador, é utilizado a função `lerEntradaPergunta()`, que tem seu funcionamento por 1 segundo, então ela é chamada 10 vezes, tendo em vista que toda vez que finalizada é decrementado 1 do contador do cronometro, utilizada para o funcionamento da leitura e medição de tempo para o cronometro.

Código comentado a baixo:

`
#include <LiquidCrystal.h>


/**
 * Declaração das variaveis, aqui criamos todas as variaveis globais
 * indo desde variaveis de controles, até mesmo as variaveis que 
 * correspondem a porta do arduino
 * 
 * instanciamos nosso lcd_1 com as portas correspondentes conectadas
 * no arduino no seu construtor
 * 
 * criamos as variaves nos quais representam os botoes (verdade, mentira, resetar)
 * 
 * variaves dos leds e do buzzer (ledVermelho,ledVerde,buzzer)
 * 
 * variaveis de controle do código ( jogada, ponteiroVerJogada, estado)
 * 
 * criamos o banco de dados das jogadas( aleatorio, perguntas, respostasPerguntas)
 * 
 * o arranjo que guarda quais perguntas foram sorteadas (perguntasEscolhidas)
 * 
 * 
 * 
 */

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
char * perguntas[] = {"Sexta tem feira?",
"Um float tem 64 bits?",
"Tem classe em C?",
"Tem classe em java?",
"Tem gerenciador de pacote em C?",
"O HTML e uma linguagem de marcacao?",
"O Python e uma linguagem de script?",
"Java e usado para desenvolvimento web?",
"CSS serve para estilizar paginas web?",
"Linux e um sistema operacional?",
"O Excel e um software de planilhas?",
"A linguagem C foi criada antes de Java?",
"A memória RAM e volatil?",
"O JavaScript e executado no servidor por padrao?",
"O SQL e usado para criar sites?"};
short respostasPergunta[] = {1,2,2,1,2,1,1,1,1,1,1,1,1,2,2};
int perguntasEscolhidas[5];


/**
 * foi criado um delay para substituir o padrão do arduino, para que neste delay
 * seja executado em meio tempo a leitura do botão de resetar, para que mesmo
 * com o jogo em espera ele esteja ouvindo o reset
 * 
 * ele funciona em um while, que decrementa uma variavel, do tipo int
 * 
 * enquanto ele le e verifica se o botão foi clickado, ele espera a partir
 * de um delay padrão de 1 milisegundo
 */
void delayMeu(int tempo){
    int timer = tempo;
    while (timer>0){
        int clicouReset = !digitalRead(resetar);
        if (clicouReset){
            estado = 0;
            return;
        }
        delay(1);
        timer--;
    }
}
/**
 * função que quando chamada aciona o buzzer e um sequencia de tons
 * formando uma pequena musica
 */
void tocarMusicaDeEspera()
{
    tone(buzzer, 710);
    delay(100);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 880);
    delay(100);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 900);
    delay(150);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 1000);
    delay(300);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 880);
    delay(200);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 1000);
    delay(300);
    noTone(buzzer);
    delay(100);
}

/**
 * Função apra verificar se a pergunta na qual foi escolhida na iterada atual
 * ja foi inserida no arranjo, para isso ele verifica todas as anteriores vendo 
 * se o valor ja foi colocado no arranjo
 */

bool ExisteNaArray(int atual,int valor){
    for(int x = 0 ;x < atual;x++){
        if(valor == perguntasEscolhidas[x]){
            return true;
        }
    }
    return false;
}
/**
 * função para gerar a sequencia, ele percorre o arranjo de tamanho 5 ja instanciado,
 * gerando numeros aleatorios e verificando se ja foram escolhidos, esses numeros estão 
 * no intervalo do tamanho da array das perguntas, ou seja, indo de 0 até quantidadeDeQuestão,
 * de forma aleatorias usando a função random(n), e ainda verificando caso o valor ja tenha
 * sido sorteado usando a função ExisteNaArray(); 
 */
void gerarSequencia(int quantidadeDeQuestao){
    for(int x=0; x < 5;x++){
        int sorteado = random(quantidadeDeQuestao);
        while(ExisteNaArray(x,sorteado)){
            sorteado = random(quantidadeDeQuestao);
        }
        perguntasEscolhidas[x] = sorteado;
    }
}
/**
 * função na qual vai tocar a escolha do botão precionado, caso a entrada seja positiva
 * o parametro no qual vai ser inserido na função é um inteiro igual a 1, chamando um outro metodo
 *  acenderLedVerde, caso seja igual a 2, é chamado o metodo acenderLedVermelho
 */
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
/**
 * Está função tem o objetivo de acender o led vermelho e ao mesmo tempo tocar o seu som correspondente
 * primeiramente ele vai acender o led, deixando em estado HIGH (logico 1) e acionand o buzzer, depois ele 
 * desativa o buzzer com um intervalo de 300 ms e depois de mais 200ms ele desativa o led
 */
void AcenderledVermelho()
{
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 262);
    delayMeu(300);
    noTone(buzzer);
    delayMeu(200);
    digitalWrite(ledVermelho, LOW);
}
/**
 * Está função tem o objetivo de acender o led verde e ao mesmo tempo tocar o seu som correspondente
 * primeiramente ele vai acender o led, deixando em estado HIGH (logico 1) e acionand o buzzer, depois ele 
 * desativa o buzzer com um intervalo de 300 ms e depois de mais 200ms ele desativa o led
 */
void AcenderledVerde()
{
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 330);
    delayMeu(300);
    noTone(buzzer);
    delayMeu(200);
    digitalWrite(ledVerde, LOW);
}
/**
 * função para verificar na interrupção caso o jogador tenha precionado o botão de resetar
 * 
 * está função vai atualizar a variavel global estado para 0 indo para o primeiro estado do jogo e 
 * tambem atualizando a variavel resetarVer para verdadeiro, para que dentro de alguns verificadores
 * logicos o loop atual seja descontinuado e forçado a retornar ao inicio
 */
void resetou()
{
    estado = 0;
    resetarVer = true;
}
/**
 * função para printar de forma longa no lcd, fazendo o scroll para a esquerda da mensagem,
 * utilizando o metodo do objeto lcd_1, scrollDisplayLeft();
 * depois de cada scrll é chamado um delayMeu, para que o scroll tenha uma velocidade 
 * aceitavel ao olho humano para ser lida
 * 
 * o metodo começa com um clear no display
 * inicializa, passando o tamanho do display(16,2)
 * printa o texto
 * coloca um delay inicial de 2 segundos
 * e depois começa um for que vai iterar caracteres vezes
 * assim dentro de cada repetição ele vai dar o scroll e esperar 150ms para a proxima iteraçao
 */
void printarLongo(char *texto, int caracteres)
{
    lcd_1.clear();
    lcd_1.begin(16, 2);
    lcd_1.print(texto);
    delayMeu(2000);
    for (int positionCounter = 0; positionCounter < caracteres; positionCounter++)
    {
        lcd_1.scrollDisplayLeft();
        delayMeu(150);
    }
}
/**
 * função parecida com a anterior, mas podendo passar o lugar de onde o texto vai aparecer,
 * podendo ser, 0 ou 1
 * dizendo qual a linha o texto sera mostrado, e tambem tendo o scroll para a esquerda para 
 * casos de onde o texto seja muito grande
 */
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
        delayMeu(150);
    }
}
/**
 * print simples, onde é recebido o texto da primeira e segunda linha com o maximo de caracters de 
 * 16, e o tempo em milisegundos no qual o texto vai ser mostrado
 * 
 * ele vai sertar o cursor para a linha de cima e vai mostrar o texto de cima,
 * ele vai sertar o cursor para a linha de baixo e vai mostrar o texto de baixo,
 * e depois vai chamar a função de delay que vai esperar o tempo passado
 */
void PrintarDuasLinhas(char *textoCima,char *textoBaixo,int TimerdelayMeu){
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(textoCima);
    lcd_1.setCursor(0, 1);
    lcd_1.print(textoBaixo);
    delayMeu(TimerdelayMeu);
}
/**
 * função chamada quando o jogador respode incorretamente, chamando algumas funções ja criadas
 * 
 * ele printa incorreto na linha de baixo com o tempo de 2 segundos,
 * depois printa tambem na linha de baixo "voltando ao inicio" com o tempo de 1 segundo
 * 
 * atualiza a variavel de controle estado para 0, e ponteiro de ver a jogada para 0 tambem. 
 */

void respondeuIncorreto()
{
    PrintarDuasLinhas("","Incorreto",2000);
    PrintarDuasLinhas("","Voltando ao inicio",1000);
    estado = 0;
    ponteiroVerJogada = 0;
}

/**
 * função para a leituda da entrada dos botões
 * 
 * os botões são setados como input pullup, por conta disso é feito a digitalRead com um not,
 * para a inversão do bit, fazendo assim a leitura mais simples.
 * 
 * ele vai fazer um while true esperando a entrada do jogador, a partir do momento do click
 * a função retornará o valor respectivo de cada botão
 * 
 * Caso click em sim, o valor retornado é 1
 * Caso click em não, o valor retornado é 2
 */

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
    }
}
/**
 * Função para ler entrada da pergunta,
 * tendo em forma de funcionamento parecido com o lerEntrada
 * ele funciona com um timer, sendo no lugar de um while true
 * um while timer > 0
 * sendo esse timer um tempo de milisegundo que é decrementado a cada repetição,
 * que contem um delay de 1 ms, sendo assim, a função vai ler apenas por 1 segundo a entrada
 * 
 * nesta função tambem é lida a entrada do botão reset, que por sua vez retorna 0, e atualiza o estado
 * global do jogo para o 0, o inicial 
 * 
 * 
 * 
 */
int lerEntradaPergunta()
{
    int timer = 1000;
    while (timer>0)
    {
        int clicouSim = !digitalRead(verdade);
        int clicouNao = !digitalRead(mentira);
        int clicouReset = !digitalRead(resetar);
        if (clicouSim){
            AcenderledVerde();
            return 1;
        }
        if (clicouNao){
            AcenderledVermelho();
            return 2;
        }
        if (clicouReset)
        {
            estado = 0;
            return 0;
        }
        delayMeu(1);
        timer--;
    }
    return -1;
}

/**
 * nesta função temos a utilização de varias outras funções
 * como a printar longo para mostrar a pergunta,
 * sprintf para criar o texto no qual representa o timer das perguntas
 * printarDuasLinhas para mostrar o numero da questão e o timer
 * alem de tambem servir para mostrar o resultado da pergunta,
 * 
 * o código funciona com 2 varias globais neste bloco, no quais vão ser utilizadas no decorrer 
 * do funcionamento da função
 * 
 * o a função começa com a função printar longo, recebendo o parametro pergunta,
 * depois um for no qual vai repetir 10 vezes, sendo esse o tempo no qual o jogador tem
 * para responder a pergunta
 * 
 * a cada repetição do for ele vai printar o timer usando a função Printar duas linhas
 * e as opções (sim ou não), após isso ele vai ler a entrada do usuario por 1 segundo,
 * usando a função lerEntradaPergunta, e a partir da resposta ele vai atualizar o display para 
 * mostrar o que foi digitado colocando um "*" na frente da opção.
 * e caso a resposta seja igual ao argumento respostaCorreta, ele vai printar: Parabens acertou! e 
 * o numero da questão.
 * 
 * Caso o for seja encerrado ou a resposta seja incorreta a função retorna -1, para controle da 
 * variavel de chances, sendo assim sendo sempre feita uma soma, fazendo o retorno da função
 * ja atualizar a variavel chance ( variavel chance é criada no estado correspondente da fase de perguntas),
 * quando o jogador acertar a pergunta a função retorna 0, fazendo assim a quantidade de chances ser mantida
 */
int perguntarParaJogador(char* pergunta,int respostaCorreta,int x,bool final){
    
        char timer[30],numeroDaQuestao[30];
        printarLongo(pergunta,25);
        for(int y = 10 ; y> 0;y--){
            sprintf(timer,"  TIMER %d",y);
            if(!final){
                sprintf(numeroDaQuestao,"Questao %d de 5",x);
            }
            else{
                sprintf(numeroDaQuestao,"Questao final!",x);
            }
            PrintarDuasLinhas(timer,"  SIM  OU  NAO",0);
            int resposta = lerEntradaPergunta();
            if(resposta == 1)PrintarDuasLinhas(timer," *SIM  OU  NAO",2000);
            if(resposta == 2)PrintarDuasLinhas(timer,"  SIM  OU *NAO",2000);
            if(resposta == respostaCorreta){
                PrintarDuasLinhas("Parabens acertou!",(char *)numeroDaQuestao,2000);
                return 0;
            }else if(resposta != respostaCorreta && resposta != -1){
                PrintarDuasLinhas("Voce errou !","Menos uma chance!",2000);
                return -1;
            }
        } 
    PrintarDuasLinhas("Voce errou !","Menos uma chance!",2000);
    return -1;
}

/**
 * função setup do arduino, tendo como objetivo setar as portas como input , output ou INPUT_PULLUP
 * é setado o botão resetar como uma interrupção (FALLING), que ao ser precionado é chamado a função resetou
 * 
 */

void setup()
{

    lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
    pinMode(buzzer, OUTPUT);
    pinMode(verdade, INPUT_PULLUP);
    pinMode(mentira, INPUT_PULLUP);
    pinMode(resetar, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(resetar), resetou, FALLING);
    randomSeed(analogRead(0));

    // Print a message to the LCD.
    Serial.begin(9600);
}


/**
 *  A Função loop
 * 
 * Função principal na qual o arduino executa em repetição eterna
 * 
 * Eu escolhi para criar este jogo uma maquina de estados, tendo uma variavel para o controle,
 * sendo "int estado", como variavel de estado, quando ela vale 0:
 * 
 * Ela gera a sequencia de perguntas, sorteia a jogada do jogo da memória, e reseta a variavel resetarVer para falso
 * printa "Jogo Sabedoria \n Sim para começar" e espera a entrada do jogador, indo para o proximo estado simplesmente
 * atualizando a variavel para 1
 * 
 * Estado == 1:
 * Printa "Jogo da memória" com a função printar Longo
 * delay de 1 segundo, printa memorizar a Sequencia com a função printar
 * itera por toda a array da sequencia usando um for indo de 0 a 5, verificando sempre caso seja precionado o botão 
 * de resetar verificando o valor armazenado no arranjo para acionar qual led acender e tocar o som
 * e indo para o estado 2
 * 
 * Estado ==2:
 *  Estado no qual vai ler a entrada em sequencia do jogador, usando um ponteiro para visualiar a posição atual se
 * analisada
 * 
 * Iniciando o código printando, clique em sequencia por 1 segundo com a função, PrintarDuasLinhas 
 * verifica se foi clickado o botão de resete olhando para a variavel de controle,
 * le a entrada do jogador com a função lerEntrada()
 * verfica se a entrada foi precionada e é verdadeira, atualizando a variavel jogadaAtual com o valor da entradaLida
 * se a entrada lida for igual ao ponteiro (ponteiroVerJogada) que observa oq dever ser digitado, ele é incrementado
 * caso incorreto é chamado a função respondeuIncorreto
 * caso o ponteiro chegue no valor de 6, ou seja, ja percorreu toda a sequencia, a variavel estado é incrementada e atualizada para 3
 * 
 * estado == 3:
 * neste estado o programa vai apenas printar em duas linhas com a função PrintarDuasLinhas(),
 * o texto "Parabens, voce \n acertou a sequencia", por um tempo de 3 segundos
 * e atualizando para o estado 4
 * 
 * estado == 4:
 *  ele vai introduzir a proxima fase que é a de perguntas, printando usando a função printar duas linhas
 * "Fase de perguntas \n"por 1 segundo e "Responda com \n Sim ou não" por 2 segundos
 * e atualiando a variavel para o valor 5
 * 
 * estado ==5:
 *  neste estado temos o jogo das perguntas, ele vai percorrer as peguntas pelo arranjo de perguntas escolhidas,
 * que armazena o indice corresponde a pergunta que está armazenada no vetor perguntas, que atraves de um while que
 * verifica a variavel short x, se ela for menor que 5.
 * 
 * a cada repetição ele vai olhar para a posição da pergunta escolhia e a resposta correspondente, e chamar a função
 * perguntarParaJogador(), que pode retorna -1 ou 0, sendo -1 quando o jogador errar e 0 se ele acertar, 
 * por conta disso fiz uma verificação, na qual observa se a quantidade de vidas do jogador + o retorno da função
 * é verdadiro ou falso, ou seja, se a vida + a resposta for > 0 (ainda existir vida) o jogador continua no jogo e o looping 
 * se mantem, fazendo assim o incremento da variavel X
 * 
 * Caso perca:
 *  caso o jogador perca todas suas vidas, é printado que o jogador perdeu,a variavel de controle perdeu se torna verdadeira, e o looping é encerrado,
 *  indo para um bloco lógico que vai verificar a variavel de derrota "perdeu", caso o jogador tenha perdido a variavel estado vira 0 retornando ao inicio
 * 
 * Caso ganhe:
 *  O jogador vai passar por todas as perguntas e o while se encerra de forma natural, indo para a verificação logica final sem atualizar a variavel de 
 *  derrota para verdadeira, fazendo assim passar o jogador para o proximo level, atualizando a variavel estado para 6
 *  
 * estado == 6:
 *  Funcionamento muito parecido com o estado 5, porem é apenas uma simples pergunta
 *  ele vai chamar a função perguntarParaJogador passando diretamente os parametros, ja que é um pergunta estática, nunca muda
 *  e vai verificar a resposta, caso seja == 0, é correta, sendo assim printando um texto usando a função
 * printarDuaslinhas e tocando a musica de espera novamente como premio
 * caso o jogador erre a resposta da pergunta ele vai printar que ele errou
 * 
 *  o jogo vai para o estado 0, incondicionalmente, ja que não temos outros estados a ir depois da pergunta final.
 *  
 * 
 * 
 * 
 */
void loop()
{
    Serial.println(estado);
    if (estado == 0)
    {
        resetarVer = false;
        jogada = random(4);
        gerarSequencia(15);
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Jogo Sabedoria");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Sim para comecar");
        if (lerEntrada() == 1)
        {
            tocarMusicaDeEspera();
            estado = 1;
        }
    }
    else if (estado == 1)
    {
        printarLongo("Jogo da memoria", 4);
        delayMeu(1000);
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
            PrintarDuasLinhas("","Correto",150);
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
        short x = 0 ;
        short vidas= 2;
        bool perdeu = 0; 
        while(x<5){
            short respostaDaPergunta = perguntarParaJogador(perguntas[perguntasEscolhidas[x]],respostasPergunta[perguntasEscolhidas[x]],x+1,false);
            if(vidas + respostaDaPergunta){
                vidas+=respostaDaPergunta;
                x++;
            }else{
                PrintarDuasLinhas("Voce perdeu !","Indo ao inicio!",2000);
                perdeu =1;
                break;
            }
        }
        if(!perdeu){
            PrintarDuasLinhas("Parabens voce ","passou!",3000);
            PrintarDuasLinhas("Agora e a hora!","A pergunta final",3000);
            PrintarDuasLinhas("Se prepare ","Essa e pesada!",3000);
            estado =6;
        }else{
            estado = 0;
        }
        
    }else if(estado == 6){
        short respostaDaPergunta = perguntarParaJogador("O cr7 e o goat",2,1,true);
        if(respostaDaPergunta==0){
            PrintarDuasLinhas("Voce eh o cara ","todo mundo sabe",3000);
            tocarMusicaDeEspera();
            PrintarDuasLinhas("que o messi eh o ","     GOAT!!!   ",3000);
            tocarMusicaDeEspera();
        }else{
            PrintarDuasLinhas("Naoooooooooo ","Voce errou!",3000);
            PrintarDuasLinhas("Perdeu o jogo! ","MESSI EH O GOAT",3000);
        }
        estado=0;
    }
}`



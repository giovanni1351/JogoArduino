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

``



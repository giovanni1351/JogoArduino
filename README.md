# JogoArduino


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

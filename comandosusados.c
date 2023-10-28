/*******************************************************************************

mqd_t: Então, mqd_t é apenas um tipo especial de variável que ajuda os programas
a trabalharem com sistemas de comunicação usando filas de mensagens

mq_open (Abrir Fila de Mensagens): Este comando é usado para criar ou abrir uma fila de mensagens, que é como um espaço
onde os processos podem enviar mensagens uns aos outros.
Pense nisso como a abertura de uma caixa de correio ou uma sala de bate-papo online
para que diferentes partes de um programa possam se comunicar.
Foi usado para abrir filas de mensagens em 
diferentes partes do programa, no Processo C, Processo A e Processo B.

mq_close (Fechar Fila de Mensagens): Este comando é usado para encerrar uma fila de mensagens
após seu uso, o que significa que você não quer mais receber ou enviar mensagens por meio dessa fila.
É semelhante a fechar a caixa de correio ou sair de uma sala de bate-papo online quando você não precisa mais dela.
Em seu exemplo, as filas de mensagens foram fechadas em todos os processos
(Processo C, Processo A e Processo B) antes de sair do programa para garantir que os recursos
associados às filas sejam liberados adequadamente.

mq_send (Enviar Mensagem para Fila): Este comando é usado para enviar uma mensagem para uma fila de mensagens. Em outras palavras,
é como colocar uma mensagem em uma caixa de correio ou enviar uma mensagem em uma sala de bate-papo online.
Por exemplo, o Processo A usou mq_send para enviar valores (n1 e n2) para Processo B por
meio de uma fila chamada QUEUE_A_TO_B. Processo C também usou mq_send para enviar ordens "A" ou "B"
para coordenar o comportamento de Processo A e Processo B.

mq_receive (Receber Mensagem da Fila): Este comando é usado para receber mensagens de uma fila de mensagens.
É como verificar a caixa de correio para ver se há alguma mensagem nova ou ver as mensagens em uma sala de 
bate-papo online.Por exemplo, o Processo B usou mq_receive para receber os valores n1 e n2 
enviados por Processo A por meio da fila QUEUE_A_TO_B. Processo C também usou mq_receive para receber as ordens
"A" ou "B" dos processos A e B a fim de coordenar seu comportamento.

Sobre o const char:
Imagine que você tem caixas de correio especiais para enviar mensagens entre computadores. Essas caixas de 
correio tratam as mensagens como pacotes de bytes, que são pedacinhos de informações. Quando você envia ou recebe
uma mensagem, ela é vista como um pacote de bytes, não importando se é texto ou qualquer outra coisa.
O const char* que você viu no código é apenas uma maneira de representar esses pacotes de bytes. É como uma caixa
especial que pode conter qualquer tipo de informação. Pode ser texto, números, imagens, ou praticamente qualquer 
coisa que possa ser quebrada em pedacinhos menores (bytes) e guardada na caixa.
Então, quando você envia uma mensagem, você a coloca nessa caixa, que é representada pelo const char*. 
E quando alguém a recebe, eles sabem que precisam pegar essa caixa e saber como abri-la para ver o que tem 
dentro. Por exemplo, se você enviou um número, a pessoa que recebe deve saber que dentro da caixa há um número.
o const char* é como uma caixa mágica que pode conter qualquer tipo de informação, e as caixas de correio especiais 
para computadores tratam tudo como pacotes de bytes. Quem envia e quem recebe precisa saber o que está dentro da caixa 
para usá-la da maneira certa.

*******************************************************************************/


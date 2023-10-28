#include <stdio.h>           // Inclui a biblioteca padrao de entrada e saida.
#include <stdlib.h>          // Inclui a biblioteca padrao de funcoes uteis, como alocacao dinamica de memoria.
#include <string.h>          // Inclui a biblioteca de manipulacao de strings.
#include <fcntl.h>           // Inclui a biblioteca para operacoes de controle de arquivos.
#include <sys/stat.h>        // Inclui a biblioteca para manipulacao de informacoes de arquivos.
#include <mqueue.h>          // Inclui a biblioteca de filas de mensagens POSIX.
#include <unistd.h>          // Inclui a biblioteca para funcoes de sistema Unix.

#define QUEUE_A_TO_B "/queue_a_to_b" // Define um nome para a fila de mensagens de A para B.
#define QUEUE_B_TO_A "/queue_b_to_a" // Define um nome para a fila de mensagens de B para A.
#define QUEUE_ORDER "/queue_order"   // Define um nome para uma fila de ordens.

int main() {
    mqd_t queue_a_to_b, queue_b_to_a, queue_order; // Declara variaveis para as filas de mensagens e atributos.
    struct mq_attr attr;                           // Declara uma estrutura para atributos da fila.
    int n1, n2, soma;                              // Declara variaveis para numeros e soma.

    attr.mq_flags = 0;             // Define as flags da fila de mensagens.
    attr.mq_maxmsg = 10;           // Define o numero maximo de mensagens na fila.
    attr.mq_msgsize = sizeof(int); // Define o tamanho das mensagens na fila.
    attr.mq_curmsgs = 0;           // Inicializa o numero de mensagens na fila.

    // Abre as filas de mensagens
    if ((queue_a_to_b = mq_open(QUEUE_A_TO_B, O_RDONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila A para B falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }
    if ((queue_b_to_a = mq_open(QUEUE_B_TO_A, O_WRONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila B para A falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }
    if ((queue_order = mq_open(QUEUE_ORDER, O_RDONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila de ordens falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }

    while (1) {
        // Aguarde a ordem do processo A
        int order;
        if (mq_receive(queue_order, (char*) &order, sizeof(int), NULL) < 0) {
            perror("mq_receive"); // Se a recepcao da ordem de A falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Aguarde n1 do processo A
        if (mq_receive(queue_a_to_b, (char*) &n1, sizeof(int), NULL) < 0) {
            perror("mq_receive"); // Se a recepcao de n1 de A falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Aguarde n2 do processo A
        if (mq_receive(queue_a_to_b, (char*) &n2, sizeof(int), NULL) < 0) {
            perror("mq_receive"); // Se a recepcao de n2 de A falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        soma = n1 + n2; // Realize a soma dos numeros recebidos.

        printf("Processo B recebeu: %d e %d\n", n1, n2); // Exibe os numeros recebidos.

        // Envie a soma de volta para o processo A
        if (mq_send(queue_b_to_a, (const char*) &soma, sizeof(int), 0) < 0) {
            perror("mq_send"); // Se o envio da soma para A falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Aguarde 1 segundo
        sleep(1); // Pausa a execucao por 1 segundo.
    }

    mq_close(queue_a_to_b); // Fecha a fila A para B.
    mq_close(queue_b_to_a); // Fecha a fila B para A.
    mq_close(queue_order);  // Fecha a fila de ordens.

    return 0; // Retorna 0 para indicar que o programa foi concluido com sucesso.
}

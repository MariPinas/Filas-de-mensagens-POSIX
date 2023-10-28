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
    if ((queue_a_to_b = mq_open(QUEUE_A_TO_B, O_WRONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila A para B falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }
    if ((queue_b_to_a = mq_open(QUEUE_B_TO_A, O_RDONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila B para A falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }
    if ((queue_order = mq_open(QUEUE_ORDER, O_WRONLY)) < 0) {
        perror("mq_open"); // Se a abertura da fila de ordens falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }

    while (1) {
        // Gere numeros aleatorios para n1 e n2
        n1 = rand() % 100; // Gera um numero aleatorio entre 0 e 99 para n1.
        n2 = rand() % 100; // Gera um numero aleatorio entre 0 e 99 para n2.

        printf("Processo A enviou: %d e %d\n", n1, n2); // Exibe os numeros gerados.

        // Envie n1 para o processo B
        if (mq_send(queue_a_to_b, (const char*) &n1, sizeof(int), 0) < 0) {
            perror("mq_send"); // Se o envio de n1 para B falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Envie n2 para o processo B
        if (mq_send(queue_a_to_b, (const char*) &n2, sizeof(int), 0) < 0) {
            perror("mq_send"); // Se o envio de n2 para B falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Envie uma ordem para o processo B
        int order = 1; // Define um codigo de ordem (1 neste caso).
        if (mq_send(queue_order, (const char*) &order, sizeof(int), 0) < 0) {
            perror("mq_send"); // Se o envio da ordem para B falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        // Aguarde a resposta do processo B (soma)
        if (mq_receive(queue_b_to_a, (char*) &soma, sizeof(int), NULL) < 0) {
            perror("mq_receive"); // Se a recepcao da soma de B falhar, exibe uma mensagem de erro e sai.
            exit(1);
        }

        printf("Processo A recebeu a soma: %d\n", soma); // Exibe a soma recebida.

        sleep(1); // Pausa a execucao por 1 segundo.
    }

    mq_close(queue_a_to_b); // Fecha a fila A para B.
    mq_close(queue_b_to_a); // Fecha a fila B para A.
    mq_close(queue_order);  // Fecha a fila de ordens.

    return 0; // Retorna 0 para indicar que o programa foi concluido com sucesso.
}

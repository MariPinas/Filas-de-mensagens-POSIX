#include <stdio.h>           // Inclui a biblioteca padrao de entrada e saida.
#include <stdlib.h>          // Inclui a biblioteca padrao de funcoes uteis, como alocacao dinamica de memoria.
#include <string.h>          // Inclui a biblioteca de manipulacao de strings.
#include <fcntl.h>           // Inclui a biblioteca para operacoes de controle de arquivos.
#include <sys/stat.h>        // Inclui a biblioteca para manipulacao de informacoes de arquivos.
#include <mqueue.h>          // Inclui a biblioteca de filas de mensagens POSIX.

#define QUEUE_A_TO_B "/queue_a_to_b" // Define um nome para a fila de mensagens de A para B.
#define QUEUE_B_TO_A "/queue_b_to_a" // Define um nome para a fila de mensagens de B para A.
#define QUEUE_ORDER "/queue_order"   // Define um nome para uma fila de ordens.

int main() {
    struct mq_attr attr; // Declara uma estrutura para atributos da fila.

    attr.mq_flags = 0;             // Define as flags da fila de mensagens.
    attr.mq_maxmsg = 10;           // Define o numero maximo de mensagens na fila.
    attr.mq_msgsize = sizeof(int); // Define o tamanho das mensagens na fila.
    attr.mq_curmsgs = 0;           // Inicializa o numero de mensagens na fila.

    mqd_t queue_a_to_b, queue_b_to_a, queue_order; // Declara variaveis para as filas de mensagens.

    // Crie as filas de mensagens
    queue_a_to_b = mq_open(QUEUE_A_TO_B, O_CREAT | O_RDWR, 0666, &attr); // Cria a fila A para B.
    if (queue_a_to_b < 0) {
        perror("mq_open"); // Se a criacao da fila A para B falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }

    queue_b_to_a = mq_open(QUEUE_B_TO_A, O_CREAT | O_RDWR, 0666, &attr); // Cria a fila B para A.
    if (queue_b_to_a < 0) {
        perror("mq_open"); // Se a criacao da fila B para A falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }

    queue_order = mq_open(QUEUE_ORDER, O_CREAT | O_RDWR, 0666, &attr); // Cria a fila de ordens.
    if (queue_order < 0) {
        perror("mq_open"); // Se a criacao da fila de ordens falhar, exibe uma mensagem de erro e sai.
        exit(1);
    }

    // Feche as filas de mensagens apos cria-las
    mq_close(queue_a_to_b); // Fecha a fila A para B.
    mq_close(queue_b_to_a); // Fecha a fila B para A.
    mq_close(queue_order);  // Fecha a fila de ordens.

    return 0; // Retorna 0 para indicar que o programa foi concluido com sucesso.
}

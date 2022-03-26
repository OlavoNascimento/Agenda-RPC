/* Cliente RPC simples */
#include <stdio.h>
#include "agenda.h"

void add(CLIENT *clnt) {
// TODO
}

void read(CLIENT *clnt) {
// TODO
}

void update(CLIENT *clnt) {
// TODO
}

void delete(CLIENT *clnt) {
// TODO
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    int loop = 1;
    int escolha;
    /* verifica se o cliente foi chamado corretamente */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    /* cria uma struct CLIENT que referencia uma interface RPC */
    clnt = clnt_create(argv[1], ADDSUB_PROG, ADDSUB_VERSION, "udp");

    /* verifica se a refer�ncia foi criada */
    if (clnt == (CLIENT *) NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }


    while (loop)
    {
        printf("Escolha uma das opções\n");
        printf("1 - Adicionar\n");
        printf("2 - Consultar\n");
        printf("3 - Modificar\n");
        printf("4 - Excluir\n");
        printf("5 - Sair\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            // TODO
            // add()
            break;
        case 2:
            // TODO
            // read()
            break;
        case 3:
            // TODO
            // update()
            break;
        case 4:
            // TODO
            // delete()
            break;
        case 5:
            loop = 0;
            break;
        default:
            break;
        }
    }

    return (0);
}

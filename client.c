/* Cliente RPC simples */

#include <stdio.h>

#include "contacts.h"
#include "lista.h"

/* função que chama a RPC add_1 */
int add(CLIENT *clnt) {
    Pessoa pessoa = {
        .nome = "Teste",
        .endereco = "Teste",
        .telefone = "Teste",
    };
    int *result;
    printf("Realizei chamada: add %s %s %s\n", pessoa.nome, pessoa.endereco, pessoa.telefone);

    /* junta os parâmetros em um struct */

    /* chama a função remota */
    result = add_1(&pessoa, clnt);
    if (result == NULL) {
        printf("Problemas ao chamar a função remota\n");
        exit(1);
    }

    return (*result);
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;

    /* verifica se o cliente foi chamado corretamente */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s hostname action\n", argv[0]);
        fprintf(stderr, "Possible actions:\n");
        fprintf(stderr, "\tadd $nome $endereço $telefone\n");
        exit(1);
    }

    /* cria uma struct CLIENT que referencia uma interface RPC */
    clnt = clnt_create(argv[1], CONTACTS_PROG, CONTACTS_VERSION, "udp");

    /* verifica se a referência foi criada */
    if (clnt == (CLIENT *) NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    /* executa os procedimentos remotos */
    add(clnt);
    clnt_destroy(clnt);

    return (0);
}

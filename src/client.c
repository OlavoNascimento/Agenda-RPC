/* Cliente RPC simples */

#include <stdio.h>
#include <string.h>

#include "agenda.h"
#include "contato.h"
#include "lista.h"
#include "logging.h"

/* função que chama a RPC add_1 */
void add(CLIENT *clnt) {
    char nome[50] = {'\0'};
    char endereco[100] = {'\0'};
    char telefone[20] = {'\0'};
    printf("Adicionando novo contato.\n");
    printf("Nome: ");
    scanf("%s", nome);
    printf("Endereço: ");
    scanf("%s", endereco);
    printf("Telefone: ");
    scanf("%s", telefone);

    int *result;
    LOG_INFO("Realizei chamada: add %s %s %s\n", nome, endereco, telefone);
    Contato *contato = contato_criar(nome, nome, endereco, telefone);

    /* chama a função remota */
    result = add_1(contato, clnt);
    if (result == NULL) {
        LOG_ERRO("Problemas na comunicação para adicionar novo contato\n");
        exit(1);
    }
    printf("Contato %s adicionado com sucesso!\n", nome);
    contato_destruir(contato);
}

void search(CLIENT *clnt) {
    char *nome = calloc(sizeof *nome, 50);
    printf("Buscando contato.\n");
    printf("Nome: ");
    scanf("%s", nome);

    LOG_INFO("Realizei chamada: search %s\n", nome);
    /* chama a função remota */
    Contato *resultado = search_1(&nome, clnt);
    if (resultado == NULL) {
        LOG_ERRO("Problemas na comunicação para procurar um contato\n");
        exit(1);
    }
    if (strcmp(resultado->nome, "") == 0) {
        LOG_ERRO("Não foi possível encontrar o contato %s na lista de contatos!\n", nome);
        exit(1);
    }
    printf("Informações do contato:\n");
    printf("\tNome: %s\n", resultado->nome);
    printf("\tEndereço: %s\n", resultado->endereco);
    printf("\tTelefone: %s\n", resultado->telefone);
    free(nome);
}

void update(CLIENT *clnt){
    char *nome_busca = calloc(sizeof *nome_busca, 50);

    char nome[50] = {'\0'};
    char endereco[100] = {'\0'};
    char telefone[20] = {'\0'};

    printf("Nome do contato para modificar: ");
    scanf("%s", nome_busca);
    Contato *resultado = search_1(&nome_busca, clnt);

    printf("Novo nome: ");
    scanf("%s", nome);
    printf("Novo endereço: ");
    scanf("%s", endereco);
    printf("Novo telefone: ");
    scanf("%s", telefone);

    contato_modificar(resultado, nome, endereco, telefone);
    LOG_INFO("Realizei chamada: update %s\n", nome_busca);
    /* chama a função remota */

    update_1(resultado, clnt);

    printf("\tContato modificado para:\n");
    printf("\tNome: %s\n", resultado->nome);
    printf("\tEndereço: %s\n", resultado->endereco);
    printf("\tTelefone: %s\n", resultado->telefone);
    free(nome_busca);
}

void delete (CLIENT *clnt) {
    char *nome = calloc(sizeof *nome, 50);
    printf("Nome do contato que quer deletar: ");
    scanf("%s", nome);

    LOG_INFO("Realizei chamada: delete %s\n", nome);
    /* chama a função remota */
    Contato *resultado = delete_1(&nome, clnt);
    printf("Deletando o contato:\n");
    printf("\tNome: %s\n", resultado->nome);
    printf("\tEndereço: %s\n", resultado->endereco);
    printf("\tTelefone: %s\n", resultado->telefone);

    // free(nome);
    contato_destruir(resultado);

}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    int loop = 1;
    int escolha;
    /* verifica se o cliente foi chamado corretamente */
    if (argc < 2) {
        LOG_ERRO("Uso: %s hostname $ação\n", argv[0]);
        exit(1);
    }

    /* cria uma struct CLIENT que referencia uma interface RPC */
    clnt = clnt_create(argv[1], AGENDA_PROG, AGENDA_VERSION, "tcp");

    /* verifica se a referência foi criada */
    if (clnt == (CLIENT *) NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    while (loop) {
        printf("Escolha uma das opções\n");
        printf("1 - Adicionar\n");
        printf("2 - Consultar\n");
        printf("3 - Modificar\n");
        printf("4 - Excluir\n");
        printf("5 - Sair\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                add(clnt);
                break;
            case 2:
                search(clnt);
                break;
            case 3:
                // TODO
                update(clnt);
                break;
            case 4:
                // TODO
                delete(clnt);
                break;
            case 5:
                loop = 0;
                break;
            default:
                break;
        }
    }

    clnt_destroy(clnt);
    return (0);
}

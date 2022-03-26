#include <stdio.h>

#include "contacts.h"
#include "lista.h"
#include "logging.h"

static Lista contatos = NULL;

static const char *obter_nome_pessoa(void *pessoa) {
    return ((Pessoa *) pessoa)->nome;
}

/* implementação da função add */
int *add_1_svc(Pessoa *pessoa, struct svc_req *rqstp) {
    static int status = 0;
    if (!contatos) {
        contatos = lista_criar(obter_nome_pessoa);
        if (!contatos) {
            LOG_ERRO("Falha ao criar lista de contatos!\n");
            return (&status);
        };
    }

    printf("Recebi chamada: add %s %s %s\n", pessoa->nome, pessoa->endereco, pessoa->telefone);
    if (!lista_inserir_final(contatos, pessoa)) {
        status = 1;
    }

    return (&status);
}


#include <stdio.h>
#include <string.h>

#include "agenda.h"
#include "contato.h"
#include "lista.h"
#include "logging.h"

static Lista contatos = NULL;

/* implementação da função add */
int *add_1_svc(Contato *contato, struct svc_req *rqstp) {
    static int status = 0;
    if (!contatos) {
        contatos = lista_criar(contato_obter_nome);
        if (!contatos) {
            LOG_ERRO("Falha ao criar lista de contatos!\n");
            return (&status);
        };
    }

    Contato *novo_contato = contato_criar(contato->nome, contato->endereco, contato->telefone);
    printf("Recebi chamada: add %s %s %s\n", novo_contato->nome, novo_contato->endereco,
           novo_contato->telefone);
    if (!lista_inserir_final(contatos, novo_contato)) {
        status = 1;
    }

    return (&status);
}

/* implementação da função search */
Contato *search_1_svc(char **nome, struct svc_req *rqstp) {
    printf("Recebi chamada: search %s\n", *nome);
    if (!contatos) {
        printf("Não é possível consultar uma lista de contatos vazia!\n");
        return contato_criar("", "", "");
    }

    ListaNo no = lista_buscar(contatos, *nome);
    if (!no) {
        LOG_INFO("%s não foi encontrado na lista de contatos\n", *nome);
        return contato_criar("", "", "");
    }

    Contato *busca = lista_obter_info(no);
    LOG_INFO("Encontrado nome: %s, endereço: %s, telefone: %s na lista de contatos\n", busca->nome,
             busca->endereco, busca->telefone);
    return busca;
}

/* implementação da função update */
Contato *update_1_svc(ContatoUpdate *updateInfo, struct svc_req *rqstp) {
    printf("Recebi chamada: update %s\n", updateInfo->nome);
    if (!contatos) {
        LOG_INFO("Não é possível modificar um contato em uma lista de contatos vazia!\n");
        return contato_criar("", "", "");
    }

    ListaNo no = lista_buscar(contatos, updateInfo->nome);
    if (!no) {
        LOG_INFO("%s não foi encontrado na lista de contatos para modificação\n", updateInfo->nome);
        return contato_criar("", "", "");
    }
    Contato *atualizado = contato_criar(updateInfo->novo->nome, updateInfo->novo->endereco,
                                        updateInfo->novo->telefone);
    ListaInfo contato_antigo = lista_definir_info(no, atualizado);
    contato_destruir(contato_antigo);
    return updateInfo->novo;
}

/* implementação da função delete */
Contato *delete_1_svc(char **nome, struct svc_req *rqstp) {
    printf("Recebi chamada: delete %s\n", *nome);
    if (!contatos) {
        printf("Não é possível consultar e deletar em uma lista de contatos vazia!\n");
        return contato_criar("", "", "");
    }

    LOG_INFO("Buscando: %s\n", *nome);
    ListaNo no = lista_buscar(contatos, *nome);

    if (!no) {
        LOG_INFO("%s não foi encontrado na lista de contatos para ser deletado\n", *nome);
        return contato_criar("", "", "");
    }

    Contato *busca_delete = lista_remover(contatos, no);
    return busca_delete;
}

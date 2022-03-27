#include <string.h>

#include "agenda.h"
#include "logging.h"

#define INIT_STRING(destiny, origin, size)           \
    do {                                             \
        destiny = calloc(sizeof *destiny, size + 1); \
        strncpy(destiny, origin, size);              \
    } while (0);

Contato *contato_criar(const char *nome, const char *nome_antigo, const char *endereco, const char *telefone) {
    Contato *novo_contato = calloc(sizeof *novo_contato, 1);
    INIT_STRING(novo_contato->endereco, endereco, 100)
    INIT_STRING(novo_contato->nome_antigo, nome_antigo, 50)
    INIT_STRING(novo_contato->nome, nome, 50)
    INIT_STRING(novo_contato->telefone, telefone, 20)
    return novo_contato;
}

void *contato_modificar(Contato *contato, const char *nome, const char *endereco, const char *telefone) {
    strcpy(contato->nome_antigo, contato->nome);
    strcpy(contato->endereco, endereco);
    strcpy(contato->nome, nome);
    strcpy(contato->telefone, telefone);
}

void contato_destruir(Contato *contato) {
    free(contato->endereco);
    free(contato->nome);
    free(contato->telefone);
    free(contato->nome_antigo);
    contato = NULL;
}

const char *contato_obter_nome(void *contato) {
    return ((Contato *) contato)->nome;
}

#ifndef CONTATO_H
#define CONTATO_H

#include "agenda.h"

Contato *contato_criar(const char *nome, const char *endereco, const char *telefone);

const char *contato_obter_nome(void *contato);

void contato_destruir(Contato *contato);

#endif

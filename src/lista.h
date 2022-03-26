#ifndef LISTA_H
#define LISTA_H

typedef struct Lista_s *Lista;
typedef struct ListaNo_s *ListaNo;

typedef void *ListaInfo;

typedef void (*MapInfoLista)(ListaInfo);
typedef const char *ObterIdentificadorLista(ListaInfo info);

/*
Itera por todos os nós de uma lista.
Será criado um ListaNo com o nome especificado. A variável lista deve ser do tipo Lista e não nula.
Não é possível remover um nó durante a iteração!
*/
#define for_each_lista(nome, lista) \
    for (ListaNo nome = lista_obter_inicio(lista); nome != NULL; nome = lista_obter_proximo(nome))

Lista lista_criar(ObterIdentificadorLista obter_identificador_info);

/*
Insere um elemento no final da lista.
Ambos os parâmetros não podem ser nulos, o parâmetro lista deve ser uma lista existente.
Retorna o endereço para o elemento adicionado.
*/
ListaNo lista_inserir_final(Lista lista, const ListaInfo info);

/*
Insere um elemento posterior a um determinado nó "p".
Todos os parâmetros não podem ser nulos e o parâmetro p deve ser um elemento válido da lista.
É retornado o endereço do elemento inserido.
*/
ListaNo lista_inserir_antes(Lista lista, ListaInfo info, ListaNo no);

/*
Insere um elemento anterior a um determinado nó "p".
Todos os parâmetros não podem ser nulos e o parâmetro p deve ser um elemento válido da lista.
É retornado o endereço do elemento inserido.
*/
ListaNo lista_inserir_depois(Lista lista, ListaInfo info, ListaNo no);

/*
Remove um elemento da lista.
Todos os parâmetros não podem ser nulos e o parâmetro lista deve ser uma lista existente.
*/
ListaInfo lista_remover(Lista lista, ListaNo no);

/*
Acessa um nó da lista.
O id passado deve ser válido. A lista deve ter uma função de busca registrada!.
Retorna o endereço do nó.
*/
ListaNo lista_buscar(Lista lista, const char *id);

/*
Troca as informações armazenadas em dois nós.
Ambos os parâmetros não podem ser nulos.
Os nós tem suas informações trocadas.
*/
void lista_trocar_info(ListaNo no1, ListaNo no2);

/*
Acessa o primeiro elemento da lista
O parâmetro lista não pode ser nulo, deve ser uma lista existe e a lista não pode estar vazia.
Retorna o endereço do primeiro nó.
*/
ListaNo lista_obter_inicio(Lista lista);

/*
Acessa o último elemento da lista.
O parâmetro lista não pode ser nulo, deve ser uma lista existe e a lista não pode estar vazia.
Retorna o endereço do último nó.
*/
ListaNo lista_obter_fim(Lista lista);

/*
Acessa as informações de um nó.
O parâmetro p não pode ser NULL e deve indicar um endereço válido que esteja na lista.
Retorna o endereço para as informações do nó especificado por p.
*/
ListaInfo lista_obter_info(ListaNo no);

/*
Acessa o elemento posterior ao elemento p.
Ambos parâmetros não podem ser nulos e o parâmetro p deve indicar um endereço válido que esteja na
lista.
Retorna o endereço do elemento posterior de p.
*/
ListaNo lista_obter_proximo(ListaNo no);

/*
Acessa o elemento anterior ao elemento p.
Ambos parâmetros não podem ser nulos e o parâmetro p deve indicar um endereço válido que esteja na
lista.
Retorna o endereço do elemento posterior de p.
*/
ListaNo lista_obter_anterior(ListaNo no);

/*
Libera a memória alocada em todos os elementos da lista.
O parâmetro lista não pode ser nulo e deve ser uma lista existente.
*/
void lista_destruir(Lista lista);

#endif

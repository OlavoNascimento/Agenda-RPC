/* agenda.x : definição da interface */

#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

/* Tipo de dado que será passado aos procedimentos remotos */
struct Contato {
    string nome<50>;
    string endereco<100>;
    string telefone<20>;
};

/* Struct para atualizar */
struct ContatoUpdate {
    string nome<50>;
    Contato *novo;
};

/* Definição da interface que será oferecida aos clientes */
program AGENDA_PROG {
    version AGENDA_VERSION {
        int ADD (Contato) = 1;
        Contato SEARCH (string) = 2;
        Contato UPDATE (ContatoUpdate) = 3;
        Contato DELETE (string) = 4;
    }
    = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

/* agenda.x : definição da interface */

#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

/* Tipo de dado que será passado aos procedimentos remotos */
struct Contato {
    string nome<50>;
    string endereco<100>;
    string telefone<20>;
};

/* Definição da interface que será oferecida aos clientes */
program AGENDA_PROG {
    version AGENDA_VERSION {
        int ADD (Contato) = 1;
        Contato SEARCH (string) = 2;
        int UPDATE (Contato) = 3;
        int DELETE (char *nome) = 4;
    }
    = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

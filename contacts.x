/* contacts.x : definição da interface */

#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

/* Tipo de dado que será passado aos procedimentos remotos */
struct Pessoa {
    string nome<50>;
    string endereco<100>;
    string telefone<20>;
};

/* Definição da interface que será oferecida aos clientes */
program CONTACTS_PROG {
    version CONTACTS_VERSION {
        int ADD (Pessoa) = 1;
    }
    = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

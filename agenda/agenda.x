/* addsub.x : defini��o da interface */


#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

/* tipo de dado que ser� passado aos procedimentos remotos */

struct contato
{
        char nome[50];
        char endereco[100];
        char telefone[30];
};

/* Defini��o da interface que ser� oferecida aos clientes */

program AGENDA_PROG
{
   version AGENDA_VERSION
   {
     int ADD (contato) = 1;
     contato READ (char *nome) = 2;
     int UPDATE (contato) = 3;
     int DELETE (char *nome) = 4;
   }
   = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

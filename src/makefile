# Verifica se uma flag de linking está disponível.
define check_ld_flag
  $(shell $(LD) $(1) -e 0 /dev/null 2>/dev/null && echo $(1))
  @rm -f a.out
endef

# Nome do executável
SERVER = server
CLIENT = client

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -fstack-protector-all -std=c99 -O3 -I /usr/include/tirpc -I .
# Flags de linking
LDFLAGS = -lnsl
LDFLAGS += $(call check_ld_flag,-ltirpc)

RPCFILE_NAME = agenda
RPC_SOURCE = $(RPCFILE_NAME).x
RPC_OUTPUT = $(RPCFILE_NAME)_xdr.c

all: $(SERVER) $(CLIENT)

# Opções para debug
# -g inclui informação de debug, permite o valgrind exibir informações de linha e nome de função.
debug: CFLAGS += -g -D DEBUG -W -Wall -Wno-unused-parameter -Wno-unused-variable -Wno-cast-function-type
debug: $(SERVER) $(CLIENT)

$(SERVER): $(RPC_OUTPUT)
	@echo "Criando executável $(SERVER)..."
	$(CC) $(CFLAGS) -o $@ contato.c server.c lista.c $(RPCFILE_NAME)_svc.c $^ $(LDFLAGS)

$(CLIENT): $(RPC_OUTPUT)
	@echo "Criando executável $(CLIENT)..."
	$(CC) $(CFLAGS) -o $@ contato.c client.c $(RPCFILE_NAME)_clnt.c $^ $(LDFLAGS)

$(RPC_OUTPUT): $(RPC_SOURCE)
	rpcgen -C $^

clean:
	rm -f *.o a.out $(RPCFILE_NAME).h $(RPCFILE_NAME)_svc.c $(RPCFILE_NAME)_xdr.c $(RPCFILE_NAME)_clnt.c $(CLIENT) $(SERVER) vgcore.*


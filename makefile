# Nome do executável
SERVER = server
CLIENT = client

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -fstack-protector-all -std=c99 -O3 -I /usr/include/tirpc -I .
# Flags de linking
LDFLAGS = -lnsl -ltirpc

RPCFILE_NAME = contacts
RPC_SOURCE = $(RPCFILE_NAME).x
RPC_OUTPUT = $(RPCFILE_NAME)_xdr.c

all: $(SERVER) $(CLIENT)

# Opções para debug
# -g inclui informação de debug, permite o valgrind exibir informações de linha e nome de função.
debug: CFLAGS += -g -D DEBUG -W -Wall -Wno-unused-parameter -Wno-unused-variable -Wno-cast-function-type
debug: $(SERVER) $(CLIENT)

$(SERVER): $(RPC_OUTPUT)
	@echo "Criando executável $(SERVER)..."
	$(CC) $(CFLAGS) -o $@ server.c lista.c $(RPCFILE_NAME)_svc.c $^ $(LDFLAGS)

$(CLIENT): $(RPC_OUTPUT)
	@echo "Criando executável $(CLIENT)..."
	$(CC) $(CFLAGS) -o $@ client.c $(RPCFILE_NAME)_clnt.c $^ $(LDFLAGS)

$(RPC_OUTPUT): $(RPC_SOURCE)
	rpcgen -C $^

clean:
	rm -f *.o $(RPCFILE_NAME).h $(RPCFILE_NAME)_svc.c $(RPCFILE_NAME)_xdr.c $(RPCFILE_NAME)_clnt.c $(CLIENT) $(SERVER) vgcore.*


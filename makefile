# Nome do executável
SERVER = server
CLIENT = client

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -fstack-protector-all -std=c99 -O3 -I /usr/include/tirpc -I /usr/include/rpcsvc -I .
# Flags de linking
LDFLAGS = -lnsl -ltirpc

RPC_SOURCE = addsub.x
RPC_OUTPUT = addsub_xdr.c

all: $(SERVER) $(CLIENT)

# Opções para debug
# -g inclui informação de debug, permite o valgrind exibir informações de linha e nome de função.
debug: CFLAGS += -g -D DEBUG -W -Wall
debug: $(SERVER) $(CLIENT)

$(SERVER): $(RPC_OUTPUT)
	@echo "Criando executável $(SERVER)..."
	$(CC) $(LDFLAGS) -o $@ server.c addsub_svc.c $^

$(CLIENT): $(RPC_OUTPUT)
	@echo "Criando executável $(CLIENT)..."
	$(CC) $(LDFLAGS) -o $@ client.c addsub_clnt.c $^

$(RPC_OUTPUT): $(RPC_SOURCE)
	rpcgen -C $^

clean:
	rm -f *.o addsub.h addsub_svc.c addsub_xdr.c addsub_clnt.c $(CLIENT) $(SERVER)


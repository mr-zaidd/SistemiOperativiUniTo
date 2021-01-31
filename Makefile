CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c89 -pedantic -IC -D W=60 -D H=20

BIN = bin/
BUILD = build/

.PHONY : rmFolder mkFolder clean compile

mkFolder:
	mkdir -p $(BUILD)
	mkdir -p $(BIN)

rmFolder:
	rm -rf $(BUILD)
	rm -rf $(BIN)

clean:
	rm -rf $(BUILD)*
	rm -rf $(BIN)*

compile: app

# INIZIO COMPILAZIONE

compilazioneMappa: src/libs/mappa.c src/include/mappa.h
	$(CC) $(CFLAGS) -c src/libs/mappa.c -o build/mappa.o

app: src/app.c compilazioneMappa
	$(CC) $(CFLAGS) src/app.c build/mappa.o -o bin/app

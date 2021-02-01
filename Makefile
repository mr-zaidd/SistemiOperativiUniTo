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

compilazioneParse: src/libs/parse.c src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/parse.c -o build/parse.o

compilazioneMappa: src/libs/mappa.c src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/mappa.c -o build/mappa.o

app: src/app.c compilazioneParse compilazioneMappa
	$(CC) $(CFLAGS) src/app.c build/mappa.o -o bin/app

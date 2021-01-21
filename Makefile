CC = gcc
CFLAGS = -Wall -g -O2 -std=c89 -pedantic -IC

BIN = bin/
BUILD = build/

.PHONY : rmFolder mkFolder clean compile run

mkFolder:
	mkdir -p $(BUILD)
	mkdir -p $(BIN)

rmFolder:
	rm -rf $(BUILD)
	rm -rf $(BIN)

clean:
	rm -rf $(BUILD)*
	rm -rf $(BIN)*

run: compile
	./bin/app

compile: bin/app

# INIZIO COMPILAZIONE

compilazioneMappa: src/libs/mappa.c src/include/mappa.h
	$(CC) $(CFLAGS) -c src/libs/mappa.c -o build/mappa.o

bin/app: src/app.c compilazioneMappa
	$(CC) $(CFLAGS) src/app.c build/mappa.o -o bin/app

CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c89 -pedantic -IC -D W=10 -D H=20

BIN = bin/
BUILD = build/
TMP = bin/tmp/
EXE = bin/exe/

.PHONY : rmFolder mkFolder clean compile

mkFolder:
	mkdir -p $(EXE)
	mkdir -p $(TMP)
	mkdir -p $(BUILD)
	mkdir -p $(BIN)

rmFolder:
	rm -rf $(EXE)
	rm -rf $(TMP)
	rm -rf $(BUILD)
	rm -rf $(BIN)

clean:
	rm -rf $(BIN)*
	mkdir -p $(TMP)
	mkdir -p $(EXE)
	rm -rf $(BUILD)*

compile: app

taxiHandler: src/exe/taxiHandler.c src/include/mylib.h src/include/inc.h
	$(CC) $(CFLAGS) src/exe/taxiHandler.c build/mylib.o -o bin/exe/taxiH


myLib: src/libs/mylib.c src/include/mylib.h src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/mylib.c -o build/mylib.o

app: src/app.c src/include/inc.h myLib taxiHandler
	$(CC) $(CFLAGS) src/app.c build/mylib.o -o bin/app

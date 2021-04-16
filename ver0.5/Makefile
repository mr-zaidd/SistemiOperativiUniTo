CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c89 -pedantic -IC -D W=2 -D H=20

BIN = bin/
BUILD = build/
TMP = bin/tmp/

.PHONY : rmFolder mkFolder clean compile

mkFolder:
	mkdir -p $(TMP)
	mkdir -p $(BUILD)
	mkdir -p $(BIN)

rmFolder:
	rm -rf $(TMP)
	rm -rf $(BUILD)
	rm -rf $(BIN)

clean:
	rm -rf $(BIN)*
	mkdir -p $(TMP)
	rm -rf $(BUILD)*

compile: app

myLib: src/libs/mylib.c src/include/mylib.h src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/mylib.c -o build/mylib.o

app: src/app.c src/include/inc.h myLib
	$(CC) $(CFLAGS) src/app.c build/mylib.o -o bin/app

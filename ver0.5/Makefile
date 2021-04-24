CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c89 -pedantic -IC -D W=30 -D H=30

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

compile: conf key shm app

#taxiHandler: src/exe/taxiHandler.c src/include/mylib.h src/include/inc.h
#	$(CC) $(CFLAGS) src/exe/taxiHandler.c build/mylib.o -o bin/exe/taxiH

#myLib: src/libs/mylib.c src/include/mylib.h src/include/inc.h
#	$(CC) $(CFLAGS) -c src/libs/mylib.c -o build/mylib.o

shm: src/libs/shmLibs.c src/include/inc.h src/include/shmLibs.h
	$(CC) $(CFLAGS) -c src/libs/shmLibs.c -o build/shmLibs.o

key: src/libs/key.c src/include/inc.h src/include/key.h
	$(CC) $(CFLAGS) -c src/libs/key.c -o build/key.o

# QUESTA REGOLA NON VIENE VISTA DA MAKE
conf: src/libs/conf.c src/include/inc.h src/include/conf.h
	$(CC) $(CFLAGS) -c src/libs/conf.c -o build/conf.o

app: src/app.c src/include/inc.h
	$(CC) $(CFLAGS) src/app.c build/shmLibs.o build/conf.o build/key.o -o bin/app

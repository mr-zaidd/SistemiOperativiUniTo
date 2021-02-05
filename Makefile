CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c89 -pedantic -IC -D W=10 -D H=20

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

# INIZIO COMPILAZIONE

compilazioneTaxi: src/exec/taxi.c src/include/mappa.h
	$(CC) $(CFLAGS) src/exec/taxi.c build/mappa.o -o bin/taxi

compilazioneMasterTaxi: src/exec/mTaxi.c
	$(CC) $(CFLAGS) src/exec/mTaxi.c -o bin/mTaxi

compilazioneRichiesta: src/exec/richiesta.c
	$(CC) $(CFLAGS) src/exec/richiesta.c -o bin/richiesta

compilazioneMasterRichieste: src/exec/mRichieste.c
	$(CC) $(CFLAGS) src/exec/mRichieste.c -o bin/mRichieste

compilazioneSigLib: src/libs/sigLib.c src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/sigLib.c -o build/sigLib.o

compilazioneParse: src/libs/parse.c src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/parse.c -o build/parse.o

compilazioneMappa: src/libs/mappa.c src/include/inc.h
	$(CC) $(CFLAGS) -c src/libs/mappa.c -o build/mappa.o

app: src/app.c compilazioneParse compilazioneMappa compilazioneSigLib compilazioneMasterRichieste compilazioneRichiesta compilazioneMasterTaxi compilazioneTaxi
	$(CC) $(CFLAGS) src/app.c build/mappa.o build/parse.o build/sigLib.o -o bin/app

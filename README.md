# PROGETTO SISTEMI OPERATIVI 20/21 UNITO

## Struttura

La cartella bin contiene i binari generati dalla compilazione ottenuta grazie al Makefile.
La cartella build contiene i file oggetto.
conf.csv è il file di configurazione.
La cartella src contiene il codice sorgente:

+ app: main del progetto, imposta i parametri del file di configurazione, crea la mappa in memoria
  condivisa, genera due figli: Master Richieste e Master Taxi, imposta un timer attraverso la
syscall alarm() e dealloca tutte le IPCS prima della terminazione o se riceve segnali di Interrupt.

+ exec: contiene i file sorgenti per quanto riguarda Master Richieste e Master Taxi che si occupano
  della gestione dei propri processi figli rispettivamente richiesta e taxi. Questi sono i processi
che effettuano le modifiche all'interno della memoria condivisa tramite la coda di messaggi.

+ include: contiene i file header necessari per i file oggetto.

+ libs: contiene i file sorgenti delle librerie.


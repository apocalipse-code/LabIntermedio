# README - Progetto Intermedio 

## Nome gruppo
Il gruppo si chiama "gruppo di Max e Lucas"

## Composizione del gruppo
Il progetto è stato svolto in un gruppo da 3 elementi:
- Baldan Massimo
- Huber Lucas
- Moratto Andrea

## Obiettivo  
Il progetto si basa sull’implementazione delle classi:

- Lettura: struttura per memorizzare 6 valori double relativi a una singola lettura;
- Misura: insieme di 17 oggetti Lettura;
- MyVector: classe implementata in laboratorio;
- InertialDriver: buffer circolare per salvare ed eseguire operazioni con varie Misure;


## Scelte di design strutturale 
Abbiamo preso la decisione di organizzare il codice nella seguente maniera:

- Lettura: struct con membri privati
- Misura: classe con un array di Letture
- InertialDriver: classe con un membro MyVector per il buffer


## Suddivisione dei compiti
- Attività svolte dal membro Andrea Moratto:
	- implementazione della struct Lettura
	- implementazione dell'operator<< per la struct Lettura
	- implementazione dei costruttori della classe Misura (file header e .cpp) 
	
- Attività svolte dal membro Lucas Huber:
	- implementazione della funzione membro "clear_buffer" di InertialDriver
	- implementazione della funzione membro "get_reading" di InertialDriver
	- implementazione dell'operator<< per InertialDriver
	- implementazione di un tester 
	- debugging/risoluzione bug

- Attività svolte dal membro Massimo Baldan: 
	- implementazione della classe MyVector con template (header e .hpp) 
	- implementazione delle funzioni della classe Misura 
	- implementazione delle funzioni "push_back" e "pop_front" di InertialDriver
	- implementazione dei costruttori e altre funzioni di InertialDriver
	- debugging/risoluzione bug


## Problemi riscontrati durante lo sviluppo
Durante l’implementazione sono emersi vari problemi e imprevisti:

- Template e MyVector:
   La classe MyVector ha richiesto particolare attenzione per evitare:
   - memory leaks,
   - doppi delete,
   - shallow copy indesiderate
   - errori sintattici e semantici nell'uso dei template
   
   Confermiamo che tutti i bug relativi a questa classe sono stati risolti e non si dovrebbero
   riscontrare comportamenti anomali da essa.
   
- Eccezioni e gestione degli errori:
   È stato necessario aggiungere diversi controlli sui parametri per evitare comportamenti indefiniti,
   soprattutto:
   - accesso fuori indice,
   - buffer vuoto,
   - funzioni che richiedono una dimensione minima del vettore.

   Consigliamo caldamente che tutte le eccezioni vengano gestite nel tester con blocchi try/catch.
   Richiediamo cortesemente di prestare attenzione ai commenti delle funzioni, dato che spiegano le 
   specifiche di utilizzo per evitare undefined behaviour. 
   
   Confermiamo che tutti i bug sono stati risolti, sono stati eseguiti test, e non si dovrebbero
   quindi riscontrare comportamenti anomali provenienti da questa categoria di bug.

  
- Errori di linking:
   All’inizio il progetto non linkava a causa di riferimenti indefiniti negli #include   
   I problemi sono stati causato da:
   - errati include,
   - uso di <file.h> invece di "file.h",
   - manca aggiunta dei file .cpp nel comando per la compilazione

   Dopo aver sistemato i percorsi e il comando di build, la compilazione funziona correttamente.

- Errori runtime:
   Abbiamo riscontrato un caso di chiamata ricorsiva della funzione size() per una svista nel codice,
   che abbiamo prontamente risolto. Oltre a questo, non sono stati rilevati errori runtime durante
   il nostro testing. 
   
   
   Confermiamo che i file del progetto compilano, linkano ed eseguono senza comportamenti imprevisti. 
   
   
##Test eseguiti 
Abbiamo eseguito i test per le "situazioni estreme" a cui la classe potrebbe essere sottoposta:
- pop e push con buffer vuoto
- alto numero di pop 
- alto numero di push
- passaggio di parametri invalidi nei costruttori 
- passaggio di indici invalidi (negativi o al di fuori del range consentito)

 
##Comandi utilizzati 
Abbiamo utilizzato i seguenti comandi per la verifica del codice:
   - compilazione: g++ -c Misura.cpp InertialDriver.cpp Tester.cpp
   - linking: g++ Misura.cpp InertialDriver.cpp Tester.cpp -o Tester
   - esecuzione: ./Tester
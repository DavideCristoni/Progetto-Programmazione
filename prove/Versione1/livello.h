#ifndef LIVELLO_H

#define LIVELLO_H

#include "oggetto.h"

class livello {
protected:
	FILE* file;
	const char nomefile[15] = { "mappa.txt" };
	int livAtt, livMax;
	listpntr liv;

public:
	livello();

	void chiudi(); //chiude il file e libera la lista degli oggetti di un livello

	listpntr livelloSuccessivo();

	listpntr livelloPrecedente();

	listpntr getLiv(); //ritorna il puntatore alla lista livello

	int getLivAtt(); //ritorna il livello attualmente caricato

	int getLivMax(); //ritorna il livello massimo generato

	
private:

	listpntr cancellaLivello();

	listpntr caricaLivello(); //legge i livello di numero livAtt

	listpntr generaLivello(); //genera livello con difficolta livMax

	oggetto* objGenerator(int type, int posx, int globaly); //genera un ogetto a partire dal suo tipo

	int leggiIntArray(char source[], char car, int& cont); //legge, all'interno dell'array, il numero prima di un char

	listpntr objListGenerator(char l[]); //genera la lista di oggetti a partire dalla stringa letta su file

	void arrayInsert(char a[], char c, int& cursore); //inserisce nell'array un char e porta avanti il cursore

	void arrayInsert(char a[], int n, int& cursore); //inserisce nell'array un char e porta avanti il cursore

	void livStringGeneator(char c[]); //traduce la lista livellogenerata nella stringa a stampare su file

	listpntr generaMappa();

	listpntr push(listpntr l1, listpntr l2);
};

#endif
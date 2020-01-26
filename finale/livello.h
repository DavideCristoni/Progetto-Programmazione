#ifndef LIVELLO_H

#define LIVELLO_H

#include "oggetto.h"

class livello {
protected:
	FILE* file;
	const char nomefile[15] = { "mappa.txt" };
	int livAtt, livMax, livLong;
	listpntr liv;

public:
	livello();

	void chiudi(); //chiude il file e libera la lista degli oggetti di un livello

	listpntr livelloSuccessivo(int &lung);

	listpntr livelloPrecedente(int &lung);

	listpntr getLiv(int &lung); //ritorna il puntatore alla lista livello

	int getLivAtt(); //ritorna il livello attualmente caricato

	int getLivMax(); //ritorna il livello massimo generato

	int getLivLong(); //ritorna la lunghezza del livello

	listpntr resetLivello();//resetta lo stato dei vari oggetti
	
private:

	void cancellaLivello();

	void caricaLivello(); //legge i livello di numero livAtt

	void generaLivello(); //genera livello con difficolta livMax

	void objListGenerator(int nObj); //genera la lista di oggetti a partire dalla stringa letta su file

	void livStringGeneator(int nObj); //traduce la lista livellogenerata nella stringa a stampare su file

};

#endif
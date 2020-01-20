#include "livello.h"
#include "libreria.h"
#include <iostream>
	//sostituire quel mostro di interpretazione per usare effettivamente la formattazione di fscanf e fprintf

	livello::livello() {
		file = fopen("mappa.txt", "w+");
		if (file == NULL)
			exit(1);
		livAtt = 1;
		livMax = 1;
		liv = generaLivello(); // comprende anche la salvaLivello;
	}

	listpntr livello::cancellaLivello() { //libera la lista livello
		while (liv != NULL) {
			listpntr temp=liv;
			liv = liv->next;
			delete temp->val;
			delete temp;
		}
		return NULL;
	}

	listpntr livello::livelloSuccessivo() { //carica o genera e carica il livelo successivo
		livAtt++;
		if (livAtt > livMax) {
			livMax = livAtt;
			cancellaLivello();
			return generaLivello();
		}
		else {
			cancellaLivello();
			return caricaLivello();
		}
	} 

	listpntr livello::livelloPrecedente() { //carica il livello precedente, se non esiste restituisce NULL
		livAtt--;
		if (livAtt == 0) {
			return NULL;
		}
		else {
			cancellaLivello();
			return caricaLivello();
		}
	}

	listpntr livello::caricaLivello() { //legge i livello di numero livAtt
		char c[500];
		rewind(file);
		fscanf(file, "%s", c);
		std::cout << atoi(c)<<" "<< livAtt;
		while (atoi(c) != livAtt)
			fscanf(file, "%s", c);
		return objListGenerator(c);
	}

	listpntr livello::generaLivello(){  //genera livello con difficolta livMax
		liv = generaMappa();
		char c[1000];
		livStringGeneator(c);
		fprintf(file, "%s\n", c);
		return liv;
	}

	oggetto* livello::objGenerator(int type, int posx, int globaly) { //crea l'oggetto di codice type e ne restituisce il puntatore
		oggetto* ris;
		if (type == 1) { //batteria
			ris = new oggetto(type, posx, globaly, 1, 1, 0, BATTERY, BATTERYTXTR, true);
			return ris;
		}
		else if (type == 2) { //buca
			ris = new oggetto(type, posx, globaly, 4, 3, BUCA, 0, BUCATXTR, false);
			return ris;
		}
	}

	int livello::leggiIntArray(char source[], char car, int& cont) { //scorre l'array fino a un certo carattere e ne restituisce l'intero che compariva prima
		int i = 0;
		char temp[10];
		while (source[cont] != car) {
			temp[i] = source[cont];
			i++;
			cont++;
		}
		cont++;
		return atoi(temp);
	}

	listpntr livello::objListGenerator(char l[]) { //dato ciòche legge nel file, genera la lista di oggetti e la restituisce
		int liv, nobj;
		int c = 0;
		listpntr ris = NULL;
		listpntr punt = NULL;
		liv = leggiIntArray(l, '_', c);			//legge quale livello è
		nobj = leggiIntArray(l, ':', c);		//legge qanti oggetti sono prsenti nel livello
		for (int i = 0; i < nobj; i++) {
			int obj = leggiIntArray(l, '@', c);	//legge il codice dell'oggetto
			int posx = leggiIntArray(l, '|', c);//legge la posizione x dell'oggetto
			int globaly = leggiIntArray(l, '#', c);//legge la posizione x dell'oggetto
			if (punt == NULL) {
				ris = new lista;
				punt = ris;
				punt->val = objGenerator(obj, posx, globaly);
				punt->next = NULL;
			}
			else {
				punt->next = new lista;
				punt = punt->next;
				punt->val = objGenerator(obj, posx, globaly);
				punt->next = NULL;
			}
		}
		return ris;
	}

	void livello::livStringGeneator(char c[]) { //traduce l'attribuo lista livello in una stringa da stampare in file
		int cursore = 0, nobj=0;
		arrayInsert(c, livMax, cursore);
		arrayInsert(c, '_', cursore);
		arrayInsert(c, 100, cursore);
		arrayInsert(c, ':', cursore);
		listpntr temp = liv;
		while (temp != NULL) {
			oggetto* obj = temp->val;
			arrayInsert(c, obj->getType(), cursore);
			arrayInsert(c, '@', cursore);
			arrayInsert(c, obj->getPosX(), cursore);
			arrayInsert(c, '|', cursore);
			arrayInsert(c, obj->getGloalY(), cursore);
			arrayInsert(c, '#', cursore);
			nobj++;
			temp = temp->next;
		}
		c[cursore] = '\0';
		//c[2] = nobj;
	}

	listpntr livello::getLiv()
	{
		return liv;
	}

	int livello::getLivAtt()
	{
		return livAtt;
	}

	int livello::getLivMax()
	{
		return livMax;
	}

	void livello::arrayInsert(char a[], char c, int &cursore) {
		a[cursore] = c;
		cursore++;
	}

	void livello::arrayInsert(char a[], int n, int& cursore) {
		char temp[10];
		_itoa(n, temp, 10);
		int i = 0;
		while (temp[i] != '\0') {
			a[cursore] = temp[i];
			cursore++; 
			i++;
		}
	}

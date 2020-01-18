#define _CRT_SECURE_NO_WARNINGS
#include "libreria.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

oggetto* objGenerator(int type, int posx, int globaly) {
	oggetto* ris;
	if (type == 1) { //batteria
		ris = new oggetto(type, posx, globaly, 1, 1, 0, BATTERY, BATTERYTXTR, true);
		return ris;
	}
	else if (type = 2) { //buca
		ris = new oggetto(type, posx, globaly, 4, 3, BUCA, 0, BUCATXTR, false);
		return ris;
	}
}

int leggiIntArray(char source[], char car, int& cont) {
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

listpntr objListGenerator(char l[]) {
	int liv, nobj;
	int c = 0;
	listpntr ris = NULL;
	listpntr punt = NULL;
	liv = leggiIntArray(l, '_', c);			//legge quale livello �
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

void leggiLivello(FILE* f, char c[], int liv) {
	rewind(f);
	fscanf(f, "%s", c);
	while (atoi(c) != liv)
		fscanf(f, "%s", c);
}

void scriviLivello(FILE* f, char file[], char liv[]) {
	fclose(f);
	f = fopen(file, "a+");
	if (f == NULL)
		exit(1);
	fprintf(f, "\n%s", liv);
}

void stampaLivello(listpntr liv) {
	listpntr temp = liv;
	while (temp != NULL) {
		temp->val->stampa();
		temp = temp->next;
	}
}

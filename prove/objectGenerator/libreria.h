#ifndef LIB1_H
#include "oggetto.h"
#define LIB1_H

oggetto* objGenerator(int type, int posx, int globaly);

listpntr objListGenerator(char l[]);

void leggiLivello(FILE* f, char c[], int liv);

void scriviLivello(FILE* f, char file[], char liv[]);

void stampaLivello(listpntr liv);

#endif
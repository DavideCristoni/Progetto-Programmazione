#include <iostream>
#include<time.h>
#include<stdlib.h>
#include"levelgenerator.h"
#include"libreria.h"

using namespace std;


void spawn(listpntr head) {
	listpntr head = new lista;
	srand(time(NULL));
	//Numero di corsie larghe 4 caratteri l'una (come la macchina)
	int ncas = (COLS - OFFSET_MENU - 4) / 4;
	//vettore che serve per dei controlli che devo ancora implementare
	int flag[ncas];
	//variabile per far sì che ci sia almeno una corsia vuota
	int vuoto;
	//questo for fa sì che ogni x caratteri della mappa si creino ostacoli e/o batterie
	for (int j = 20; j < 500; j = j + 10)
	{
		//possibile creazione di un oggetto in ogni corsia
		for (int i = 0; i < ncas; i++)
		{
			//calcolo della corsia che sarà vuota nella prossima sezione
			vuoto = rand() % ncas + 1;
			//BATTERIE (1x1)
			//calcolo della probabilità di generarsi della batteria (30%)
			if (rand() % 101 >= 70)
			{
				//i indica la corsia (partendo da 0) quindi moltiplicandola per 4 e sommando 2 abbiamo il carattere esatto della sua x (il +1 è per far sì che la batteria sia più centrale)
				lista_oggetti(head, 1, i * 4 + 2 + 1, j);
			}
			//BUCHE (4x3)
			else
			{
				//controllo per non creare buche nella corsia che deve essere libera
				if (vuoto != ncas)
				{
					//calcolo della probabilità di generarsi della buca (20%%)
					if (rand() % 101 > 80)
					{
						lista_oggetti(head, 2, i * 4 + 2, j);
					}
				}
			}
		}
	}
}

//funzione di inserimento dell'oggetto generato in lista
void lista_oggetti(listpntr head, int type, int posx, int Globaly) {
	srand(time(NULL));
	if (head != NULL) {
		listpntr tmp = head;
		while (tmp->next != NULL) tmp = tmp->next;
		tmp = new listpntr;
		tmp->val = objGenerator(1, posx, Globaly);
		tmp->next = NULL;
	}
	else {
		head = new listpntr;
		head->val = objGenerator(1, posx, Globaly);
		head->next = NULL;
	}
}

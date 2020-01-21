#include<iostream>
#include<time.h>
#include<stdlib.h>
#include"levelgenerator.h"
#include"libreria.h"
#include"oggetto.h"
#include"math.h"

using namespace std;

int item_creator(listpntr head, int level) {
	
	head = new lista;
	int n_obj = 0;
	srand(time(NULL));
	//Numero di corsie larghe 4 caratteri l'una (come la macchina)
	int ncas = (COLS - OFFSET_MENU - 4) / 4;
	//vettore che serve per dei controlli che devo ancora implementare
	int flag[ncas];
	//variabile per far sì che ci sia almeno una corsia vuota
	int last;
	last = rand() % ncas;
	for(int k=0; k<ncas; k++)
	{
		if(last != k)
		{
			flag[k]=1;
		}
	}
	//probabilità batterie e ostacoli
	float per_bat = min(90 + 0.2 * level, 95.0) ;
	float per_ost = max(50 + 0.2 * level, 50.0) ;
	//questo for fa sì che ogni x caratteri della mappa si creino ostacoli e/o batterie
	for (int j = 20; j < 500; j = j + 10)
	{
		//possibile creazione di un oggetto in ogni corsia
		for (int i = 0; i < ncas; i++)
		{
			
			//BATTERIE (1x1)
			//calcolo della probabilità di generarsi della batteria (30%)
			if (rand() % 101 >= per_bat)
			{
				//i indica la corsia (partendo da 0) quindi moltiplicandola per 4 e sommando 2 abbiamo il carattere esatto della sua x (il +1 è per far sì che la batteria sia più centrale)
				lista_oggetti(head, 1, i * 4 + 2 + 1, j);
				flag[i] = 0;
				n_obj++;
			}
			//BUCHE (4x3)
			else
			{
				//controllo per non creare buche nella corsia che deve essere libera
					if(last != i)
				{
					//calcolo della probabilità di generarsi della buca (20%%)
					if (rand() % 101 >= per_ost)
					{
						lista_oggetti(head, 2, i * 4 + 2, j);
						flag[i] = 1;
						n_obj++;
					}
					else flag[i] = 0;
				}
			}
		}
		//percorso libero
		if(last!= 4 && last != 0)
		{
			
			if(flag[last + 1] == 0)
			{
				if(flag[last - 1] == 0)
				{
					if(rand() % 3 == 1) last = last + 1;
					else if(rand() % 3 == 2) last = last - 1;
				}
				else
				{
					if(rand() % 2 == 1) last = last + 1;
				}
			}
		}
		else if(last == 4)
		{
			if(flag[last - 1] == 0)
			{
				if(rand() % 2 == 0) last = last - 1;
			}
		}
		else
		{
			if(flag[last + 1] == 0)
			{
				if(rand() % 2 == 0) last = last + 1;
			}
		}
	}
	return n_obj;
}

//funzione di inserimento dell'oggetto generato in lista
void lista_oggetti(listpntr head, int type, int posx, int Globaly) {
	srand(time(NULL));
	if (head != NULL) {
		listpntr tmp = head;
		while (tmp->next != NULL) tmp = tmp->next;
		tmp = new lista;
		tmp->val = objGenerator(1, posx, Globaly);
		tmp->next = NULL;
	}
	else {
		head = new lista;
		head->val = objGenerator(1, posx, Globaly);
		head->next = NULL;
	}
}

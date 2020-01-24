#include "livello.h"
#include "levelgenerator.h"
#include <ncurses.h>
#include <time.h>

//implementare il codice di gledis

	livello::livello() {
		file = fopen(nomefile, "w+");
		if (file == NULL)
			exit(1);
		livAtt = 1;
		livMax = 1;
		liv = generaLivello(); // comprende anche la salvaLivello
	}

	void livello::chiudi()
	{
		liv = cancellaLivello();
		fclose(file);
	}

	listpntr livello::cancellaLivello() { //libera la lista livello
		while (liv != NULL) {
			listpntr temp=liv;
			liv = liv->next;
			delete temp->val; //cancella l'oggetto
			delete temp;	//cancella la struct lista di oggetti;
		}
		livLong=0;
		return NULL;
	}

	listpntr livello::livelloSuccessivo(int &lung) { //carica o genera e carica il livelo successivo
		livAtt++;
		if (livAtt > livMax) {
			livMax = livAtt;
			cancellaLivello();
			liv = generaLivello(); //brutta
			lung=livLong;
			return liv;
		}
		else {
			cancellaLivello();
			liv = caricaLivello();//brutta
			lung = livLong;
			return liv;
		}
	} 

	listpntr livello::livelloPrecedente(int &lung) { //carica il livello precedente, se non esiste restituisce NULL
		livAtt--;
		if (livAtt == 0) {
			return NULL;
		}
		else {
			cancellaLivello();
			liv = caricaLivello();//brutta
			lung = livLong;
			return liv;
		}
	}

	listpntr livello::caricaLivello() { //legge i livello di numero livAtt
		rewind(file);
		int livello, nObj;
		fscanf(file, "%d=%d_%d:", &livello, &livLong, &nObj);
		while (livello != livAtt) {
			char c;
			do {
				c = fgetc(file);
			} while (c != '\n');
			fscanf(file, "%d=%d_%d:", &livello, &livLong, &nObj);
		}
		return objListGenerator(nObj);
	}

	listpntr livello::generaLivello(){  //genera livello con difficolta livMax
	int nObj = 0;
		liv = item_creator(nObj, livMax, livLong);
		livStringGeneator(nObj);
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
		else if (type == 3) { //ghiaccio
			ris = new oggetto(type, posx, globaly, 3, 4, 0, 0, ICETXTR, true);
			return ris;
		}
		else if (type == 4) { //auto
			ris = new oggetto(type, posx, globaly, 3, 4, AUTO, 0, AUTOTXTR, true);
			return ris;
		}
		else {
			return NULL;
		}
	}

	listpntr livello::objListGenerator(int nObj) { //dato ci�che legge nel file, genera la lista di oggetti e la restituisce
		listpntr ris = NULL;
		listpntr punt = NULL;
		for (int i = 0; i < nObj; i++) {
			int type, posx, globaly;
			fscanf(file, "%d@%d|%d#", &type, &posx, &globaly);
			if (punt == NULL) {
				ris = new lista;
				punt = ris;
				punt->val = objGenerator(type, posx, globaly);
				punt->next = NULL;
			}
			else {
				punt->next = new lista;
				punt = punt->next;
				punt->val = objGenerator(type, posx, globaly);
				punt->next = NULL;
			}
		}
		fgetc(file); //smalticso la \n
		liv = ris;
		return ris;
	}

	void livello::livStringGeneator(int nObj) { //traduce l'attribuo lista livello in una stringa da stampare in file
		fprintf(file, "%d=%d_%d:", livMax, livLong, nObj);
		listpntr temp = liv;
		while (temp != NULL) {
			oggetto* obj = temp->val;
			fprintf(file, "%d@%d|%d#", obj->getType(), obj->getPosX(), obj->getGloalY());
			temp = temp->next;
		}
		fprintf(file, "\n");
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

	int livello::getLivLong()
	{
		return livLong;
	}

	listpntr livello::generaMappa()
	{
		int nObj, i = 0;
		int posx, posy, globy, type;
		listpntr l1 = NULL;
		listpntr l2 = NULL;
		srand(time(NULL));
		nObj = 50;
		while (i < nObj)
		{

			posy = 0;
			type = (rand() % 3) + 1;
			posx = (rand() % (50)) + 2;
			if (type == 2)
				posx = posx - 3;
			globy = (rand() % 20);
			l2 = new lista;
			l2->val = objGenerator(type, posx, globy);
			l1 = push(l1, l2);
			i++;
		}
		return l1;
	}

	listpntr livello::push(listpntr l1, listpntr l2)
	{
		l2->next = l1;
		return l2;
	}

	listpntr livello::resetLivello(){
		listpntr temp = liv;
		while(temp!=NULL){
			temp->val->reset();
			temp=temp->next;
		}
		return liv;
	}
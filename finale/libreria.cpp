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
		else if (type == 2) { //bomba
			ris = new oggetto(type, posx, globaly, 1, 1, 0, 0, BOMBTXTR, true);
			return ris;
		}
		else if (type == 3) { //auto
			ris = new oggetto(type, posx, globaly, 3, 4, AUTO, 0, AUTOTXTR, true);
			return ris;
		}
        else if (type == 4) { //buca
			ris = new oggetto(type, posx, globaly, 4, 3, BUCA, 0, BUCATXTR, false);
			return ris;
		}
		else if (type == 5) { //ghiaccio
            ris = new oggetto(type, posx, globaly, 3, 4, 0, 0, ICETXTR, false);
			
			return ris;
		}
		else {
			return NULL;
		}
}

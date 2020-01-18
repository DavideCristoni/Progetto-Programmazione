#include <ncurses>
#include <iostream>
#include <cstring>
using namespace std;

#define row 500 
#define col 45

class oggetto{
    protected:
	int posx, posy, globaly;
	int offsetX, offsetY;
	int type, score, battery;
	bool enable, disappearOnContact;
	char texture[10][10];

    public:
	oggetto(int type, int x, int y, int offx, int  offy, int score, const int battery, const char txtr[10][10], bool disappear){
        this->type=type;
		posx = x;
		globaly = y;
		posy = 0;
		offsetX = offx;
		offsetY = offy;
		this->score = score;
		this->battery = battery;
		enable = true;
		disappearOnContact = disappear;
		for (int i = 0; i < 10; i++)
			strcpy(texture[i], txtr[i]);
	}
        void move(){posy ++;}
        void stampa(){
            int i;
            int j = 0;
        	if(!disappearOnContact || enable){
                attron(COLOR_PAIR(type ));
                for(i = offsetY - 1; i >= 0; i --){
                    while(j < 10  && texture[i][j] != ' '){
                        mvprintw(posy - i, posx + j, "%c", texture[i][j]);
                        j++;
                        }
                    j = 0;
                    }
                attroff(COLOR_PAIR(type ));
                }
            }
        void effect(int& score, double& battery){
            if (enable) {
                score = score - this->score;
                battery = battery + this->battery;
                if (battery > 100)
                    battery = 100;
                enable = false;
                }
    	}
        int getPosx(){ return posx;}
        int getPosy(){return posy;}
        int getOffsetx(){return offsetX;}
        int getOffsety(){return offsetY;}
        int getGloby(){return globaly;}
};

struct oggetti{
    oggetto *val;
    oggetti *next;
};

oggetto* objGenerator(int type, int posx, int globaly) {
	const int BATTERY = 15;
    const char BATTERYTXTR[10][10] = { "B        ", "         ", "         ", "         ", "         ", "         ", "         ", "         ", "         ", "         ", };
    const int BUCA = 300;
    const char BUCATXTR[10][10] = { "^^^^     ", "^^^^     ", "^^^^     ", "         ", "         ", "         ", "         ", "         ", "         ", "         " };

	if (type == 1) { //batteria
		oggetto *ris = new oggetto(type,posx, globaly, 1, 1, 0, BATTERY, BATTERYTXTR, true); 
		return ris;
    	} else if (type = 2) { //buca
		oggetto *ris = new oggetto(type, posx, globaly, 4, 3, BUCA, 0, BUCATXTR, false);
		return ris;
	    }
    return NULL;
}

void lista_oggetti(oggetti* lista,int type, int posx, int Globaly){
    srand(time(NULL));
    if(lista!=NULL){
        oggetti tmp = lista;
        while(tmp!=NULL) tmp = tmp->next;
        tmp = new oggetti;
        tmp->val = objGenerator(1,rand()%posx+2, Globaly);
        tmp->next = NULL;
    } else{
        lista = new oggetti;
        lista->val = objGenerator(1,rand()%posx+2, Globaly);
        lista->next = NULL;
    }
}

bool check_place(oggetti* head,int posx, int Globly){
    //Devo cercare nella lista oggetti se sono presenti dei valori di posx simili....
    oggetti tmp = lista;
    if(posx!=0){
        while(tmp!=NULL){
            if(Globly == tmp->val->getGloby() || Globy+1 == tmp->val->getGloby()){
                   if(posx == tmp->val->getPosx()||posx+1 == tmp->val->getPosx()||posx-1 == tmp->val->getPosx())
                   return false;
            }        
            }
        }
    return true;
    }


void CreaMappa(int lvl){
    //Sistemo in modo che il giocatore possa completare il percorso
    oggetti* lista = NULL;
    int pre=0;
    for(int i = 0; i<row ;i++){
        if(lv<5){ //Livello Facile
            //Sistema le batterie
            if(i%5 == 0) lista_oggetti(lista,1,col-2,i);
            //Sistema gli ostacoli
            if(i%35 ==0){
                while(!check_place(lista,pre,i)){
                    pre = (rand()%col-2)+2;
                }
                lista_oggetti(lista,2,pre,i);
            }
            }else if(lv>=5 && lv<10){//Livello Medio                     
                if(i%7 == 0) lista_oggetti(lista,1,col-2,i);
                if(i%20 ==0){
                while(!check_place(lista,pre,i)){
                    pre = (rand()%col-2)+2;
                }
                lista_oggetti(lista,2,pre,i);
            }
                }else if(lv<=10 && lv<15){//Livello Difficile          
                    if(i%11 == 0) lista_oggetti(lista,1,col-2,i);
                    if(i%15 ==0){
                while(!check_place(lista,pre,i)){
                    pre = (rand()%col-2)+2;
                }
                lista_oggetti(lista,2,pre,i);
            }
                    }else{//Livello Hardcore
                        if(i%14 == 0) lista_oggetti(lista,1,col-2,i);
                        if(i%7 ==0){
                            while(!check_place(lista,pre,i)){
                            pre = (rand()%col-2)+2;
                            }
                            lista_oggetti(lista,2,pre,i);
                            }
                        }
        }

    }


int main(){

    return 0;
}
//Devo inserire le posizioni sullo schermo ( posx, posy, globaly)
//L'offset dell'oggetto in questione (offsetX, OffsetY)
//Influenza e tipo di come si interagiscono type, score, battery 
//Tutti gli oggetti sono enabled mentre devo inserire se 
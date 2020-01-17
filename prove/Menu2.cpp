
#include <ncurses.h>

class menu{
protected:
int score;
int energy;
public:
    menu(int score = 0, int energy = 0){
        this->score = score;
        //Controllo che l'energy non sia maggiore di 100
        if(energy>100) energy = 100;
        this->energy = energy;
    }
    void stampa_menu(){
        int col, row;
        getmaxyx(stdscr,row,col);

        for(int i=0;i<row;i++){
            mvprintw(i,col-2,"||");
            mvprintw(i,col-32,"||");
        }
        //Parametro per gestire le proporzioni
        int prm = (int)(row*0.1);

        //Nome del gioco
        mvprintw(prm+1,col-20," NEED FOR ");
        mvprintw(prm+2,col-20,"   SPEED  ");
        mvprintw(prm+4,col-20," cerignola");
        mvprintw(prm+5,col-20,"  edition ");

        //Punteggio Score
        mvprintw((prm*2)+6,col-18,"SCORE:");
        mvprintw((prm*2)+7,col-18,"%d",score);

        //Livello batteria
        mvprintw((prm*2)+9,col-18,"ENERGY:");
        mvprintw((prm*2)+10,col-18,"%d /100", energy);

        //Barra Benzina
        mvprintw((prm*3)+11,col-16," - ");
        int a;
        for(a=(prm*3)+12;a<((prm*3)+12)+(10-energy/10);a++){
            mvprintw(a,col-16,"| |");
        }
        for(a;a<(prm*3)+22;a++){
            mvprintw(a,col-16,"|#|");
        }
        mvprintw((prm*3)+22,col-16," - ");
    }
    //Funzioni che servono solo per il testing e che possono essere rimosse
    int getScore(){
        return score;
    }
    int getEnergy(){
        return energy;
    }
};

int main(){
    //Usato per testare il programma...
    initscr();
    int energy;
    menu primo;
    primo.stampa_menu();
    getch();
    menu secondo(0,20);

    //Opzionale controllo dei valori
    /*int a = secondo.getScore();
    int b = secondo.getEnergy();
    mvprintw(0,0,"Lo score è %d",a);
     mvprintw(1,0,"L'energy è %d",b);*/

    secondo.stampa_menu();
    getch();
    endwin();
    return 0;
}
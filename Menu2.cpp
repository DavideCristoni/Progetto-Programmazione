
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
        //Nome del gioco
        mvprintw(2,col-20," NEED FOR ");
        mvprintw(3,col-20,"   SPEED  ");
        mvprintw(5,col-20," cerignola");
        mvprintw(6,col-20,"  edition ");

        //Punteggio Score
        mvprintw(9,col-18,"SCORE:");
        mvprintw(10,col-18,"%d",score);

        //Livello batteria
        mvprintw(12,col-18,"ENERGY:");
        mvprintw(13,col-18,"%d /100", energy);

        //Livello Benzina con Barra
        mvprintw(18,col-16," - ");
        int a;
        for(a=19;a<19+(10-energy/10);a++){
            mvprintw(a,col-16,"| |");
        }
        for(a;a<29;a++){
            mvprintw(a,col-16,"|#|");
        }
        mvprintw(29,col-16," - ");
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
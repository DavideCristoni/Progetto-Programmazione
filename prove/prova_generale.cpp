#include "header.h"
class player
{
    protected:
        int posx, posy;
        int offsetX, offsetY;
    public:
        player(int x, int y)
        {
            posx = x;
            posy = y;
            offsetX = 3;
            offsetY = 3;
        }
        void move(char direzione, int bordoX, int bordoY)
        {
            if(direzione == 'w')
            {
                if(posy > (0 + offsetY))
                    posy--;
            }
            else if(direzione == 's')   
            {          
                if(posy < (bordoY - 1))
                posy ++;    
            }
            else if(direzione == 'a')  
            {           
                if(posx > (0+1))
                posx --;
            }
            else if(direzione == 'd')
            {
                if(posx < (bordoX - offsetX - 1))
                    posx ++;
            }
        }
        void stampa()
        {
            mvprintw(posy, posx, "***");    
            mvprintw(posy-2, posx, "/ \\");    
            mvprintw(posy-1, posx,"***");    
            mvprintw(posy-3, posx, "*_*");
        }
};

class oggetto
{
    protected:
        int posx, posy, globaly;
        int offsetX, offsetY;
        int score, battery;

    public:

        oggetto(int x)
        {
            posx = x;
            posy = 0;
            offsetX = 1;
            offsetY = 1;
        }
        void move()
        {
            posy ++;
        }
        void stampa()
        {
            mvprintw(posy, posx, "#");
        }
        void effect(int &score, int &battery)
        {
            score = score - this->score;
            battery = battery + this->battery;
        }
};

class batteria:public oggetto
{
    public:
        batteria(int x):oggetto(x)
        {}

    void stampa()
    {
        mvprintw(posy, posx, "B");
    }
};

class fosso:public oggetto
{
    public:
        fosso(int x):oggetto(x)
        {

        }

        void stampa()
        {
            mvprintw(posy, posx, "^^^^");
            mvprintw(posy-1, posx, "^");
            mvprintw(posy-2, posx, "^");
            mvprintw(posy-1, posx+3, "^");
            mvprintw(posy-2, posx+3, "^");
            mvprintw(posy-2, posx, "^^^");
            mvprintw(posy-1, posx+1, "*");
            mvprintw(posy-1, posx+2, "*");
        }
};

class mappa
{
    protected:
        struct oggetti
        {
            oggetto val;
            oggetti *next;
        };
        oggetti *lista = NULL;
        public:
            mappa()
            {

            }

};

int main()
{
    char c = 'a';
    int row , col;
    int flag  = 0;
    int time_taken;
    player p1  =  player(10, 10);
    fosso o1 = fosso(10);
    clock_t start, end;
    start = clock();
    start = start * 1000;

    inizializza();
    getmaxyx(stdscr, row, col);

    while(c != 'q')
    {
        end = clock();
        c = getch();
        if (ref(start))
        {    
            clear();
            stampa_strada(flag);
            p1.move(c, col, row);
            p1.stampa();
            flag = (flag + 1) % 5;
            o1.move();
            o1.stampa();
            refresh();
        }
        if(c == 'w' || c == 'a' || c == 's' || c == 'd')
        {
            clear();
            stampa_strada(flag);
            o1.stampa();
            p1.move(c, col, row);
            p1.stampa(); 
            refresh(); 
        }
    }
    endwin();
    return 0;
}

void stampa_strada(int flag)
{
    int x, y, maxY;
    int i = 0;
    getmaxyx(stdscr ,y, x);   
    maxY = y;
    if(flag == 0)
        y = 0;
    else if(flag == 1)
        y = 1;
    else if(flag == 2)
        y = 2;
    else if(flag == 3) 
        y = 3;
    else    
        y = 4;

    while(y < maxY)
    {
        mvaddch(y, x/2, '|');
        y = y + 5;
    }
    while(i < maxY)
    {
        mvprintw(i, 0, "||");
        i++;
    }
    i = 0;
    while(i < maxY)
    {
        mvprintw(i, x-2, "||");
        i++;
    }
}



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
            offsetY = 4;
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
        int getPosx()
        {
            return posx;
        }
        int getPosy()
        {
            return posy;
        }
        int getOffsetx()
        {
            return offsetX;
        }
        int getOffsety()
        {
            return offsetY;
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
            score = 0;
            battery = 0;
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
        int getPosx()
        {
            return posx;
        }
        int getPosy()
        {
            return posy;
        }
        int getOffsetx()
        {
            return offsetX;
        }
        int getOffsety()
        {
            return offsetY;
        }
};


class batteria:public oggetto
{
    public:
        batteria(int x):oggetto(x)
        {
            offsetY = 1;
            offsetX = 1;
            battery = 20;
        }

    void stampa()
    {
        attron(COLOR_PAIR(2));
        mvprintw(posy, posx, "B");
        attroff(COLOR_PAIR(2));
    }
};

class fosso:public oggetto
{
    public:
        fosso(int x):oggetto(x)
        {
            offsetX = 4;
            offsetY = 3;
            score = 20;
        }

        void stampa()
        {
            attron(COLOR_PAIR(3));
            mvprintw(posy, posx, "^^^^");
            mvprintw(posy-1, posx, "^");
            mvprintw(posy-2, posx, "^");
            mvprintw(posy-1, posx+3, "^");
            mvprintw(posy-2, posx+3, "^");
            mvprintw(posy-2, posx, "^^^");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(4));
            mvprintw(posy-1, posx+1, "*");
            mvprintw(posy-1, posx+2, "*");
            attroff(COLOR_PAIR(4));
        }
};

struct batterie
{
    batteria *val ;
    batterie *next;
};

struct fossi
{
    fosso *val ;
    fossi *next;
};

class mappa
{
    protected:
        batterie *listaB = NULL;
        fossi *listaF = NULL;
        public:
            mappa(batterie *l1, fossi *l2)
            {
                listaF = l2;
                listaB = l1;
            }
            void checkCollision(int &score, int &battery, player p1)
            {
                batterie *tmp;
                tmp = listaB;
                int i, j;
                bool collisione = false;
                fossi *tmp1;
                tmp1 = listaF;
               while(tmp != NULL)
                {
                    //Collisione da P1 avanti ostacolo dietro
                    for(j = 0; j < p1.getOffsetx(); j++)
                    {
                        for(i = 0; i < tmp->val->getOffsetx(); i++)
                            if(tmp->val->getPosx() + i == (p1.getPosx() + j) && (tmp->val->getPosy() - tmp->val->getOffsety() == (p1.getPosy())))
                            {
                                tmp->val->effect(score, battery);
                                collisione = true;
                            }

                    }
                    
                    //Collisione P1 da destra a sinistra
                    if(!collisione)
                    {
                        for(j = 0; j < p1.getOffsety(); j++)
                            for(i = 0; i < tmp->val->getOffsety(); i++)

                                if(tmp->val->getPosx()  == (p1.getPosx() + p1.getOffsetx()-1) && (tmp->val->getPosy() - i == (p1.getPosy() - j + 1)))
                                {
                                    tmp->val->effect(score, battery);
                                    collisione = true;
                                }
                    }

                    //Collsione da P1 da sinistra a destra
                    if(!collisione)
                    {
                        for(j = 0; j < p1.getOffsety(); j++)
                            for(i = 0; i < tmp->val->getOffsety(); i++)
                                if(tmp->val->getPosx() + tmp->val->getOffsetx() - 1  == (p1.getPosx()) && (tmp->val->getPosy() - i == (p1.getPosy() - j + 1)))
                                {
                                    tmp->val->effect(score, battery);
                                    collisione = true;
                                }   
                    }
                    if(!collisione)
                    {                    
                        for(j = 0; j < p1.getOffsetx(); j++)
                            for(i = 0; i < tmp->val->getOffsetx(); i++)
                                if(tmp->val->getPosx() + i  == (p1.getPosx() + j) && (tmp->val->getPosy() - 1 == (p1.getPosy() - p1.getOffsety() + 1)))
                                {
                                    tmp->val->effect(score, battery);
                                    collisione = true;
                                }
                    }
                    
                        //mvprintw(0, 0, "Posizione y P1: %d", p1.getPosy());
                        //mvprintw(1, 0, "Posizione y Batteria: %d", tmp1->val->getPosy());
                    tmp = tmp->next;
                }
            

               while(tmp1 != NULL)
                {
                    //Collisione da P1 avanti ostacolo dietro
                    for(j = 0; j < p1.getOffsetx(); j++)
                    {
                        for(i = 0; i < tmp1->val->getOffsetx(); i++)

                            if(tmp1->val->getPosx() + i == (p1.getPosx() + j) && (tmp1->val->getPosy() - tmp1->val->getOffsety()  == (p1.getPosy())))
                            {
                                tmp1->val->effect(score, battery);
                                collisione = true;
                            }
                        //mvprintw(0, 0, "Posizione y getPos-Offset: %d", p1.getPosy() - p1.getOffsety() + 1);
                        //mvprintw(1, 0, "Posizione y getPosy: %d", tmp1->val->getPosy());


                    }
                    
                    //Collisione P1 da destra a sinistra
                    if(!collisione)
                    {
                        for(j = 0; j < p1.getOffsety(); j++)
                            for(i = 0; i < tmp1->val->getOffsety(); i++)
                                if(tmp1->val->getPosx()  == (p1.getPosx() + p1.getOffsetx()-1) && (tmp1->val->getPosy() - i == (p1.getPosy() - j + 1)))
                                {
                                    tmp1->val->effect(score, battery);
                                    collisione = true;
                                }
                                
                    }

                    //Collsione da P1 da sinistra a destra
                    if(!collisione)
                    {
                        for(j = 0; j < p1.getOffsety(); j++)
                            for(i = 0; i < tmp1->val->getOffsety(); i++)
                                if(tmp1->val->getPosx() + tmp1->val->getOffsetx() - 1  == (p1.getPosx()) && (tmp1->val->getPosy() - i == (p1.getPosy() - j + 1)))
                                {
                                    tmp1->val->effect(score, battery);
                                    collisione = true;
                                }   
                    }

                    //Collisione da P1 da sopra a sotto
                    if(!collisione)
                    {                    
                        for(j = 0; j < p1.getOffsetx(); j++)
                            for(i = 0; i < tmp1->val->getOffsetx(); i++)
                                if(tmp1->val->getPosx() + i  == (p1.getPosx() + j) && (tmp1->val->getPosy() - 1 == (p1.getPosy() - p1.getOffsety() + 1)))
                                {
                                    tmp1->val->effect(score, battery);
                                    collisione = true;
                                }
                    }
                    

                    tmp1 = tmp1->next;
                }

            }
            void move()
            {
                fossi *tmp;
                batterie * tmp1;
                tmp = listaF;
                tmp1 = listaB;
                while(tmp != NULL)
                {
                    tmp->val->move();
                    tmp = tmp->next;
                }

                while(tmp1 != NULL)
                {
                    tmp1->val->move();
                    tmp1 = tmp1->next;
                }
            }
            void stampa()
            {
                fossi *tmp;
                batterie * tmp1;
                tmp = listaF;
                tmp1 = listaB;
                while(tmp != NULL)
                {
                    tmp->val->stampa();
                    tmp = tmp->next;
                }

                while(tmp1 != NULL)
                {
                    tmp1->val->stampa();
                    tmp1 = tmp1->next;
                }     
            }

};

class gioco
{
    protected:
        int score;
        int battery;
    public:
        gioco()
        {
            score = 1000;
            battery = 100;
        }
                struct oggetti
        {
            oggetto val;
            oggetti *next;
        };
        oggetti *lista = NULL;
        public:
};

int main()
{
    char c = 'a';
    int row , col;
    int flag  = 0;
    int time_taken;

    int score = 1000;
    int battery = 100;

    clock_t start, end;
    start = clock();
    start = start * 1000;
    fossi *l1;
    batterie *l2;
    l1 = new fossi;
    l1->val = new fosso(10);
    l1->next = NULL;
    //l1->next = new fossi;
    //l1->next->val = new fosso(30);
    //l1->next->next = NULL;

    l2 = new batterie;
    l2->val = new batteria(20);
    l2->next = NULL;
    

    mappa m1 = mappa(l2, l1);
    inizializza();
    getmaxyx(stdscr, row, col);
    player p1  =  player(10, 32);

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
            m1.move();
            m1.stampa();
            m1.checkCollision(score, battery, p1);
            mvprintw(0, 0, "Score %d", score);
            mvprintw(1, 0, "Batteria %d", battery);
            refresh();
        }
        if(c == 'w' || c == 'a' || c == 's' || c == 'd')
        {
            clear();
            stampa_strada(flag);
            p1.move(c, col, row);
            p1.stampa(); 
            m1.stampa();
            m1.checkCollision(score, battery, p1);
            mvprintw(0, 0, "Score %d", score);
            mvprintw(1, 0, "Batteria %d", battery);
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



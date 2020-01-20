#include "header.h"
#include "libreria.h"
#include "livello.h"
#include "oggetto.h"
#define OFFSET_MENU 30

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
                if(posy - offsetY > (1))
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
                if(posx < (bordoX - offsetX - 1 - OFFSET_MENU))
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


struct oggetti
{
    oggetto *val;
    oggetti *next;
};

class mappa
{
    protected:
        //batterie *listaB = NULL;
        //fossi *listaF = NULL;
        int goal;
        int limit;
        listpntr listaOggetti = NULL;
        public:
            mappa(listpntr l1, int goal)
            {
                listaOggetti = l1;
                this->goal = goal;
                limit = -200;
            }
            void checkCollision(int &score, double &battery, player p1)
            {
                listpntr tmp;
                tmp = listaOggetti;
                int i, j;
                bool collisione = false;
               while(tmp != NULL)
                {
                    //Collisione da P1 avanti ostacolo dietro
                    for(j = 0; j < p1.getOffsetx(); j++)
                    {
                        for(i = 0; i < tmp->val->getOffsetx(); i++)
                            if(tmp->val->getPosX() + i == (p1.getPosx() + j) && (tmp->val->getPosY() - tmp->val->getOffsety() == (p1.getPosy())))
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

                                if(tmp->val->getPosX()  == (p1.getPosx() + p1.getOffsetx()-1) && (tmp->val->getPosY() - i == (p1.getPosy() - j + 1)))
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
                                if(tmp->val->getPosX() + tmp->val->getOffsetx() - 1  == (p1.getPosx()) && (tmp->val->getPosY() - i == (p1.getPosy() - j + 1)))
                                {
                                    tmp->val->effect(score, battery);
                                    collisione = true;
                                }   
                    }
                    if(!collisione)
                    {                    
                        for(j = 0; j < p1.getOffsetx(); j++)
                            for(i = 0; i < tmp->val->getOffsetx(); i++)
                                if(tmp->val->getPosX() + i  == (p1.getPosx() + j) && (tmp->val->getPosY() - 1 == (p1.getPosy() - p1.getOffsety() + 1)))
                                {
                                    tmp->val->effect(score, battery);
                                    collisione = true;
                                }
                    }
                    
                        //mvprintw(0, 0, "Posizione y P1: %d", p1.getPosy());
                        //mvprintw(1, 0, "Posizione y Batteria: %d", tmp1->val->getPosy());
                    tmp = tmp->next;
                }    

                if(p1.getPosx() <= 0 + 1)
                    score = score - 105;
                        
                else if(p1.getPosx() + p1.getOffsetx() - 1 >=  COLS - 2 - OFFSET_MENU)
                    score = score - 105;
                        
            }
            void move(int globy)
            {
                listpntr tmp;
                tmp = listaOggetti;
                while(tmp != NULL)
                {
                    if(globy > tmp->val->getGloalY())
                        tmp->val->move();
                    tmp = tmp->next;
                }

            }
            void stampa(int globy)
            {
                listpntr tmp;
                tmp = listaOggetti;
                while(tmp != NULL)
                {
                    if(globy > tmp->val->getGloalY())
                    tmp->val->stampa();
                    tmp = tmp->next;
                }    
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

                attron(COLOR_PAIR(3));
                while(y < maxY)
                {
                    mvaddch(y, (x - OFFSET_MENU)/2, ' ');
                    y = y + 5;
                }
                attroff(COLOR_PAIR(3));
                while(i <= maxY)
                {
                    mvprintw(i, 0, "||");
                    i++;
                }
                i = 0;
                while(i <= maxY)
                {
                    mvprintw(i, x - OFFSET_MENU - 2, "||");
                    i++;
                }
            }
            bool check_goal(int score)
            {
                return score >= goal;
            }
            bool check_retrocedi(int score)
            {
                return score <= limit;
            }
};

class gioco
{
    protected:
        int score;
        double battery; // Batteria del giocatore
        double batteryLose; //Consumo di batteria
        int scoreGain;
        int lvl;
        int azione; // Indica se si deve ricaricare, passare, o retrocedere di livello;
        int initialGoal = 1000; // Punteggio iniziale
        bool endGame;
        livello *l;
    public:
        gioco()
        {
            score = 10;
            battery = 100;
            batteryLose = 0.4;
            scoreGain = 10;
            lvl = 1;
            endGame = false;
            l = new livello();
            azione = 1;
        }
        void start(mappa *m)
        {
            char c = 'a';
            int row , col;
            int flag  = 0;
            int time_taken;
            int globy = 0;
            clock_t start, end;
            start = clock();
            start = start * 1000;
            oggetti *l1;
           // menu men = menu();

            getmaxyx(stdscr, row, col);
            player p1  =  player(10, 20);

            while(c != 'q')
            {
                end = clock();
                c = getch();
                if (ref(start))
                {    
                    clear();
                    m->stampa_strada(flag);
                    flag = (flag + 1) % 5;
                    m->move(globy);
                    m->stampa(globy);
                    m->checkCollision(score, battery, p1);
                    score = score + scoreGain;
                    battery = battery - batteryLose; 
                    
                    p1.move(c, col, row);
                    p1.stampa();
                    //stampa_layout(score, battery, col);
                    stampa_laterale(battery, score);
                    globy++;
                    mvprintw(0, 0, "%d", globy);
                   // men.stampa_menu();
                    mvprintw(0, 0 ,"%d", globy);
                    refresh();
                }
                if(c == 'w' || c == 'a' || c == 's' || c == 'd')
                {
                    clear();
                    m->stampa_strada(flag);
                    m->stampa(globy);
                    m->checkCollision(score, battery, p1);
                    p1.move(c, col, row);
                    p1.stampa();
                    //stampa_layout(score, battery, col);
                    stampa_laterale(battery, score);
                    refresh(); 
                }
                if(check_game_over())
                {
                    stampa_game_over();
                    while(c == 'q');
                        c = getchar();
                    azione = 1; 
                    return;
                }
                if(m->check_goal(score))
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 2 , "LIVELLO COMPLETATO");
                    mvprintw(LINES / 2 + 1 , COLS - OFFSET_MENU + 2, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    azione = 2;
                    lvl++;
                    return;
                }
                if(m->check_retrocedi(score))
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 5 , "LIVELLO PERSO");
                    mvprintw(LINES / 2 + 1 , COLS - OFFSET_MENU + 2, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    lvl--;
                    azione = 3;
                    return;
                }
            }

            this->endGame = true;
            return;
        }
        mappa *genera_mappa()
        {
            mappa *m1;
            if (azione == 1)
            {
                m1 = new mappa(l->getLiv(), 100);
            }
            else if(azione == 2)
            {
                m1 = new mappa(l->livelloSuccessivo(), 100);
                
            }
            else
            {
                m1 = new mappa(l->livelloPrecedente(), 100);
                mvprintw(3, 0, "%p", l->getLiv());
            }

            return m1;
        }
        bool check_game_over()
        {
            return battery <= 0;
        }
        void stampa_game_over()
        {
            attron(COLOR_PAIR(3));
            mvprintw(LINES/2, (COLS - OFFSET_MENU - 6) /2, "YOU DIED");
            attroff(COLOR_PAIR(3));
            refresh();
        }
        void start_menu()
        {   
            char c = 'a';
            int sel = 5;
            int notSel = 4;
            int s1 = sel;
            int s2 = notSel;
            int tmp;
            inizializza();
            while(c != 13)
            {
                clear();
                mvprintw(0 + 10, COLS / 2 - 10, "NEED FOR SPEED");
                mvprintw(1 + 10, COLS / 2 - 10, "CERIGNOLA EDITION");
                if(c == 'w' || c == 's')
                {
                    tmp = s1;
                    s1 = s2;
                    s2 = tmp;
                }
                attron(COLOR_PAIR(s1));
                mvprintw(LINES / 2 - 1, COLS / 2 - 10, "START");
                attroff(COLOR_PAIR(s1));
                attron(COLOR_PAIR(s2));
                mvprintw(LINES / 2 , COLS / 2 - 10, "ESCI");
                attroff(COLOR_PAIR(s2));
                
                mvprintw(LINES - 6, 0, "COMANDI:");
                mvprintw(LINES - 5, 0, "W:Avanti\nS:Indietro\nA:Sinistra\nD:Destra");
                //mvprintw(LINES - 8, COLS/2 - 10, "Supera i livelli raggiungendo ");
                //mvprintw(LINES - 7, COLS/2 - 10, "lo score necessario!!!");
                //mvprintw(LINES - 6, COLS/2 - 10, "Attento agli ostacoli e alla batteria della tua auto!!!:");
                refresh();
                c = getchar();
            }
            if(s1 == sel)
            {
                load_level();
            }
            else
            {
                return;
            }
            
        }
        void stampa_laterale(int energy, int score)
        {
            int col, row;
            int color;
            getmaxyx(stdscr, row, col);
            int prm = (int)(row*0.1);

            //Nome del gioco
            mvprintw(prm+1,col-20," NEED FOR ");
            mvprintw(prm+2,col-20,"   SPEED  ");
            mvprintw(prm+4,col-20," Cerignola");
            mvprintw(prm+5,col-20,"  Edition ");

            mvprintw((prm*2)+6, col-18,"LV: %d" ,lvl);

            //Punteggio Score
            mvprintw((prm*2)+8,col-18,"SCORE:");
            mvprintw((prm*2)+9,col-18,"%d",score);

            //Livello batteria
            mvprintw((prm*2)+11,col-18,"ENERGY:");
            mvprintw((prm*2)+12,col-18,"%d /100", energy);

            //Barra Benzina
            mvprintw((prm*3)+13,col-16," - ");
            int a;
            for(a=(prm*3)+14;a<((prm*3)+14)+(10-energy/10);a++){
                mvprintw(a,col-16,"| |");
            }
            if(battery < 60 && battery > 25)
                color = 7;
            else if(battery <= 25)
                color = 8;
            else
                color = 6;

                for(a;a<(prm*3)+24;a++){
                mvprintw(a,col-16,"|");
                attron(COLOR_PAIR(color));
                mvprintw(a,col-15," ");
                attroff(COLOR_PAIR(color));
                mvprintw(a,col-14,"|");
            }
            mvprintw((prm*3)+24,col-16," - ");
        }
        void load_level()
        {
            mappa *m;
            while(!endGame)
            {
                m = genera_mappa();
                char c = 'a';
                reset();
                start(m);
                delete(m);
                if(lvl == 0)
                    {
                        clear();
                        endGame = true;
                        mvprintw(LINES / 2, COLS / 2 - 4 , "GAME OVER");
                        refresh();
                        while(c != ' ' && c != 'q')
                        {
                            c = getch();
                        }
                    }
            }
            endwin();
        }
        void reset()
        {
            score = 0;
            battery = 100;
        }
};

int main()
{
    gioco g1;
    g1.start_menu();
    return 0;
}

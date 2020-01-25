#include "gioco.h"


        gioco::gioco()
        {
            score = 10;
            battery = 100;
            batteryLose = 0.4;
            scoreGain = 10;
            lvl = 1;
            inizializza();
            endGame = false;
            l = new livello();
            azione = 1;
            limit = 0;
            goal = 0;
            margineLvl = 2000;

        }
        void gioco::start(mappa *m)
        {
            char c = 'a';
            int row , col;
            int flag  = 0;
            int time_taken;
            int globy = 0;
            clock_t start, end;
            start = clock();
            start = start * 1000;
            listpntr l1;
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
                if(check_goal())
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
                if(check_retrocedi())
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
                if(m->check_ricarica(globy))
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 0 , "NON SEI RIUSCITO A");
                    mvprintw(LINES / 2 + 1, COLS - OFFSET_MENU + 0 , "RAGGIUNGERE LO SCORE!!!");
                    mvprintw(LINES / 2 + 2 , COLS - OFFSET_MENU + 0, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    azione = 1;
                    return;
                }
            }

            this->endGame = true;
            initialGoal + (lvl * MOLT_LIV);
            return;
        }
        mappa *gioco::genera_mappa()
        {
            mappa *m1;
            int lunghezza;
            if(lvl == 1)
                limit = 0;
            else
                limit = 0;

            if (azione == 1)
            {
                lunghezza = l->getLivLong();
                m1 = new mappa(l->getLiv(), lunghezza * 10, limit, lunghezza);
            }
            else if(azione == 2)
            {
                m1 = new mappa(l->livelloSuccessivo(lunghezza), lunghezza * 10, limit, lunghezza);
                
            }
            else
            {
                m1 = new mappa(l->livelloPrecedente(lunghezza), lunghezza * 10, limit, lunghezza);
                //mvprintw(3, 0, "%p", l->getLiv());
            }

            if(lvl % 4 == 0)
                margineLvl = margineLvl - 500;
            if(margineLvl < 0)
                margineLvl  = 0;
            goal = (lunghezza * 10) - (margineLvl);

            return m1;
        }
        bool gioco::check_game_over()
        {
            return battery <= 0;
        }

        void gioco::stampa_game_over()
        {
            attron(COLOR_PAIR(3));
            mvprintw(LINES/2, (COLS - OFFSET_MENU - 6) /2, "YOU DIED");
            attroff(COLOR_PAIR(3));
            refresh();
        }
        void gioco::start_menu()
        {   
            char c = 'a';
            int sel = 5;
            int notSel = 4;
            int s1 = sel;
            int s2 = notSel;
            int s3 = notSel;
            int selezionato = 0;
            while(c != 13)
            {
                clear();
                mvprintw(0 + 10, COLS / 2 - 10, "NEED FOR SPEED");
                mvprintw(1 + 10, COLS / 2 - 10, "CERIGNOLA EDITION");
                if(c == 's' )
                {
                    selezionato = (selezionato + 1) % 3;
                    if(selezionato == 0)
                    {
                        s1 = sel;
                        s2 = notSel;
                        s3 = notSel;
                    }
                    else if(selezionato == 1)
                    {
                        s1 = notSel;
                        s2 = sel;
                        s3 = notSel;
                    }
                    else if(selezionato == 2)
                    {
                        s1 = notSel;
                        s2 = notSel;
                        s3 = sel; 
                    }
                }
                if(c == 'w')
                {
                    selezionato = (selezionato - 1);
                    if (selezionato < 0)
                    {
                        selezionato = 2;
                    }

                    if(selezionato == 0)
                    {
                        s3 = notSel;
                        s1 = sel;
                        s2 = notSel;
                    }
                    else if(selezionato == 1)
                    {
                        s1 = notSel;
                        s2 = sel;
                        s3 = notSel;
                    }
                    else if(selezionato == 2)
                    {
                        s1 = notSel;
                        s2 = notSel; 
                        s3 = sel;
                    }
                }
                attron(COLOR_PAIR(s1));
                mvprintw(LINES / 2 - 2, COLS / 2 - 10, "START");
                attroff(COLOR_PAIR(s1));
                attron(COLOR_PAIR(s2));
                mvprintw(LINES / 2 - 1 , COLS / 2 - 10, "ISTRUZIONI");
                attroff(COLOR_PAIR(s2));
                attron(COLOR_PAIR(s3));
                mvprintw(LINES / 2 , COLS / 2 - 10, "ESCI");
                attroff(COLOR_PAIR(s3));
                
                mvprintw(LINES - 6, 0, "COMANDI:");
                mvprintw(LINES - 5, 0, "W:Avanti\nS:Indietro\nA:Sinistra\nD:Destra");
                //mvprintw(LINES - 8, COLS/2 - 10, "Supera i livelli raggiungendo ");
                //mvprintw(LINES - 7, COLS/2 - 10, "lo score necessario!!!");
                //mvprintw(LINES - 6, COLS/2 - 10, "Attento agli ostacoli e alla batteria della tua auto!!!:");
                refresh();
                c = getchar();
            }
            if(selezionato == 0)
            {
                load_level();
            }
            else if(selezionato == 1)
            {
                stampa_istruzioni();
                start_menu();
            }
            else
            {
                return;
            }
            
        }
        void gioco::stampa_laterale(int energy, int score)
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
            mvprintw((prm*2)+9,col-24,"%.4d / %.4d / %d", limit, score, goal);

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

                for(a-=1;a<(prm*3)+24;a++){
                mvprintw(a,col-16,"|");
                attron(COLOR_PAIR(color));
                mvprintw(a,col-15," ");
                attroff(COLOR_PAIR(color));
                mvprintw(a,col-14,"|");
            }
            mvprintw((prm*3)+24,col-16," - ");
        }
        void gioco::load_level()
        {
            mappa *m;
            while(!endGame)
            {
                m = genera_mappa();
                char c = 'a';
                start(m);
                reset();
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
        void gioco::reset()
        {
            score = 0;
            if(lvl == 1)
                score = 0;
            battery = 100;
        }
        void gioco::stampa_istruzioni()
        {
            char c = 'a';
                clear();
                mvprintw(1, 10, "Fino a dove riuscirai a spingerti?");
                mvprintw(14, 1, "Raggiungi lo score necessario     ---->\n per passare di livello!!!");
                mvprintw(17, 1, "Attenzione alla batteria!!!       ---->");
                mvprintw(20, 1, "Se scenderai sotto un certo punteggio\n tornerai indietro di livello!!");
                mvprintw(24, 1, "Se invece non raggiungi lo score necessario\n rimarrai nello stesso");
                stampa_laterale(50, 1000);
                refresh();
            while(c != 13)
            {
                c = getchar();
            }
            return;
        }

        bool gioco::check_goal()
        {
            return score >= goal;
        }

        bool gioco::check_retrocedi()
        {
            return score < limit ;
        }


        bool gioco::ref(clock_t start) 
        {
            int modulo;
            int dif = 0;
            if (lvl > 10)
                dif = 200;
            if(lvl > 15)
                dif = 400;
            if(lvl > 20)
                dif = 500;

            clock_t end;
            end = clock();
            modulo = ((double)(end - start) / (double) CLOCKS_PER_SEC) * 10000;
            if (modulo % (1000 - dif) == 0) 
                return true;
            else 
                return false;
        }

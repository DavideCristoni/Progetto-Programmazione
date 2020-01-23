#include "mappa.h"
            mappa::mappa(listpntr l1, int goal, int lim, int l)
            {
                listaOggetti = l1;
                this->goal = goal;
                limit = lim;
                listaOggetti = l1;
                lunghezza = l;
            }
            void mappa::checkCollision(int &score, double &battery, player p1)
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
            void mappa::move(int globy)
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
            void mappa::stampa(int globy)
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
            void mappa::stampa_strada(int flag)
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

                attron(COLOR_PAIR(5));
                while(y < maxY)
                {
                    mvaddch(y, (x - OFFSET_MENU)/2, ' ');
                    y = y + 5;
                }
                attroff(COLOR_PAIR(5));
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

            bool mappa::check_ricarica(int globy)
            {
                return lunghezza < (globy - 40);
            }
            int mappa::getGoal()
            {
                return goal;
            }

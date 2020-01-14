#include <unistd.h>
#include <ncurses.h>


void stampa_oggetto(int &posx, int &posy);
void stampa_strada(int flag);

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
                if(posx > (0 + offsetX))
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
            mvprintw(posy, posx, "*");    
            mvprintw(posy-2, posx-2, "*****");    
            mvprintw(posy-1, posx-1,"***");    
            mvprintw(posy-3, posx, "*");
        }
};


int main()
{
    char c = 'a';
    int row , col;
    int flag  = 0;
    int pos1X = 10;
    int pos1Y = 0;
    player p1 =  player(10, 10);
    initscr(); //Crea lo schermo
    //start_color();
    //halfdelay(2);
    nodelay(stdscr, TRUE);
    initscr(); //Crea lo schermo
    //start_color();
    //halfdelay(2);
    nodelay(stdscr, TRUE);
    noecho();  //Impostazione per evitare la stampa di ciò che è premuto sulla tastiera
    //cbreak();  //Input da tastiera subito disponibile
    curs_set(0);
    getmaxyx(stdscr, row, col);
    //init_pair(1, COLOR_BLACK, COLOR_GREEN);
    //bkgd(COLOR_PAIR(1));
    while(c != 'q')
    {
        c = getch();
        clear();
        stampa_strada(flag);
        stampa_oggetto(pos1X, pos1Y);
        p1.move(c, col, row);
        p1.stampa();
        usleep(35000);
        flag = (flag + 1) % 5;
        refresh();
    }
    endwin();
    return 0;
}
void stampa_oggetto(int &posx, int &posy)
{
    posy ++;
    mvprintw(posy, posx, "#");
}

void stampa_strada(int flag )
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



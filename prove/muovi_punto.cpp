#include <ncurses.h>

void stampa_auto(int posX, int posY);

int main()
{
    char c = 'a';
    char moto[] = "****\n**\n*"; 
    int row , col;
    int posX, posY;
    initscr(); //Crea lo schermo
    noecho();  //Impostazione per evitare la stampa di ciò che è premuto sulla tastiera
    cbreak();  //Input da tastiera subito disponibile
    getmaxyx(stdscr, row, col);
    posX = row/2;
    posY = col/2;
    mvaddch(row / 2, col/2, 'A');

    while(c != 'q')
    {
        c = getch();
        if(c == 'w')
        { 
            if(posX > 0)
                posX --;
        }
        else if(c == 's')
        {
            if(posX < row-1)
                posX ++;
        }
        else if(c == 'a')
        {
            if(posY > 0)
                posY --;
        }
        
        else if(c == 'd')
        {
            if(posY < col-1)
                posY ++;
        }
        clear();
        stampa_auto(posX, posY);   
        refresh();
        
    }


}
void stampa_auto(int posX, int posY)
{
    mvprintw(posX, posY, "*");    
    mvprintw(posX-2, posY-2, "*****");    
    mvprintw(posX-1, posY-1, "***");    
    mvprintw(posX-3, posY, "*");   
    return; 
}
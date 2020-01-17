#include "header.h"

void inizializza()
{
    //system("tilix --geometry=10x100");
    nodelay(stdscr, TRUE);
    initscr(); //Crea lo schermo
    start_color();
    nodelay(stdscr, TRUE);
    noecho();  //Impostazione per evitare la stampa di ciò che è premuto sulla tastiera
    curs_set(0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    //bkgd(COLOR_PAIR(1));
}

bool ref(clock_t start) 
{
    int modulo;
    clock_t end;
    end = clock();
    modulo = ((double)(end - start) / (double) CLOCKS_PER_SEC) * 10000;
    if (modulo % 1000 == 0) 
        return true;
    else 
        return false;
}

void stampa_layout(int score, double battery, int col)
{
    mvprintw(0, 0, "Score %d", score);
    mvprintw(1, 0, "Batteria %.0f", battery);
    mvprintw(0, col - 35, "Need for speed Cerignola Edition");
}

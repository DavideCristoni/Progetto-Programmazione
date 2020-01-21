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
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_GREEN, COLOR_GREEN);
    init_pair(7, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(8, COLOR_RED, COLOR_RED);
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


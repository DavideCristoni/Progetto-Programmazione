#include <unistd.h>
#include <ncurses.h>
#include <time.h>

void stampa_oggetto(int &posx, int &posy);
void stampa_strada(int flag);
void inizializza();
bool ref(clock_t start);
void stampa_layout(int score, double battery, int col);

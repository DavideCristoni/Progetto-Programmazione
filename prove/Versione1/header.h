#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <cstring>
#include <cstdlib>
#define OFFSET_MENU 30

void stampa_oggetto(int &posx, int &posy);
void stampa_strada(int flag);
void inizializza();
bool ref(clock_t start);
void stampa_layout(int score, double batery, int col);

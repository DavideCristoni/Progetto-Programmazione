#include "mappa.h"

class gioco
{
    protected:
        int score;
        double battery; // Batteria del giocatore
        double batteryLose; //Consumo di batteria
        int scoreGain;
        int lvl;
        int azione; // Indica se si deve ricaricare, passare, o retrocedere di livello;
        int initialGoal = 0; // Punteggio iniziale
        bool endGame;
        livello *l;
    public:
        gioco();
        void start(mappa *m);
        mappa *genera_mappa();
        void stampa_game_over();
        void start_menu();
        void stampa_laterale(int energy, int score);
        void load_level();
        void reset();
        void stampa_istruzioni();
        bool check_game_over();
};
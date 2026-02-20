#ifndef GIOCO_H_INCLUDED
#define GIOCO_H_INCLUDED
#include <time.h>
#include "Tavolo.h"
#include "Stack.h"

typedef enum {
    MOD_ZEN,
    MOD_TEMPO
} Modalita;

typedef struct {
    Tavolo tavolo;
    Stack stack;
    int punteggio;
    int combo;
    Modalita modalita;
    time_t inizio;
    int tempoLimite;
    bool attiva;
} Gioco;

void inizializzaGioco(Gioco* g, Modalita m);
void aggiornaPunteggio(Gioco* g);
int tempoTrascorso(Gioco* g);
void stampaHUD(Gioco* g);

#endif // GIOCO_H_INCLUDED

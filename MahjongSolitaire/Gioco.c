#include <stdio.h>
#include <time.h>
#include "Gioco.h"
#include "Colori.h"

void inizializzaGioco(Gioco* g, Modalita m) {
    g->punteggio = 0;
    g->combo = 0;
    g->modalita = m;
    g->inizio = time(NULL);
    g->tempoLimite = 300;
    g->stack = creaStack();
    g->attiva = true;
}

void aggiornaPunteggio(Gioco* g) {
    g->combo++;
    g->punteggio += 10 + (g->combo * 5);
}

int tempoTrascorso(Gioco* g) {
    return (int)(time(NULL) - g->inizio);
}

void stampaHUD(Gioco* g) {

    printf("%sModalita:%s %s | ",
           GIALLO, RESET,
           g->modalita == MOD_ZEN ? "ZEN" : "TEMPO");

    int tempo = tempoTrascorso(g);

    printf("Tempo: %d", tempo);

    if (g->modalita == MOD_TEMPO)
        printf("/%d", g->tempoLimite);

    printf(" | Punteggio: %d | Combo x%d\n\n",
           g->punteggio, g->combo);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Tessera.h"
#include "ListaTessere.h"
#include "Tavolo.h"
#include "Stack.h"
#include "Salvataggio.h"
#include "Gioco.h"
#include "Colori.h"
#define DIM 10

void creaTessereIniziali(ListaTessere* lista) {
    int tipo, valore, copia;

    for (tipo = BAMBOO; tipo <= CARATTERI; tipo++) {
        for (valore = 1; valore <= 9; valore++) {
            for (copia = 0; copia < 2; copia++) {
                Tessera* t = creaTessera(tipo, valore);
                inserisciInTesta(lista, t);
            }
        }
    }
}


int main() {

    srand(time(NULL));
    Gioco gioco;
    ListaTessere lista = creaLista();

    int sceltaModalita;

    printf("=== MAHJONG SOLITAIRE 2.0 ===\n");
    printf("1. Modalita Zen\n");
    printf("2. Modalita Tempo (5 minuti)\n> ");
    scanf("%d", &sceltaModalita);

    Modalita m = (sceltaModalita == 2) ? MOD_TEMPO : MOD_ZEN;

    inizializzaGioco(&gioco, m);
    inizializzaTavolo(&gioco.tavolo);

    creaTessereIniziali(&lista);
    distribuisciTessere(&gioco.tavolo, &lista);

    distruggiLista(&lista);

    while (gioco.attiva) {

        if (gioco.modalita == MOD_TEMPO &&
            tempoTrascorso(&gioco) >= gioco.tempoLimite) {

            printf("\nTempo scaduto!\n");
            break;
        }

        stampaHUD(&gioco);
        stampaTavolo(&gioco.tavolo);

        if (!esistonoMossePossibili(&gioco.tavolo)) {
            printf("Partita bloccata!\n");
            break;
        }

        printf("1. Rimuovi coppia\n");
        printf("2. Undo\n");
        printf("3. Salva\n");
        printf("4. Carica\n");
        printf("0. Esci\n> ");

        int cmd;
        scanf("%d", &cmd);

        if (cmd == 0)
            break;

        if (cmd == 1) {

            int x1,y1,x2,y2;

            printf("Prima tessera (riga colonna): ");
            scanf("%d%d",&x1,&y1);
            printf("Seconda tessera (riga colonna): ");
            scanf("%d%d",&x2,&y2);

            x1--; y1--; x2--; y2--;

            if (rimuoviCoppia(&gioco.tavolo,x1,y1,x2,y2)) {

                Mossa mossa = {x1,y1,x2,y2};
                push(&gioco.stack,mossa);

                aggiornaPunteggio(&gioco);

                if (partitaFinita(&gioco.tavolo)) {
                    printf("Hai vinto!\n");
                    break;
                }

            } else {
                printf("Mossa non valida!\n");
                gioco.combo = 0;
            }
        }

        if (cmd == 2) {
            Mossa m;
            if (pop(&gioco.stack,&m)) {

                gioco.tavolo.celle[m.x1][m.y1]->rimossa=false;
                gioco.tavolo.celle[m.x2][m.y2]->rimossa=false;

                gioco.punteggio -= 5;
                gioco.combo = 0;
            }
        }
        if (cmd == 3) {
            if (salvaPartita("partita.bin", &gioco))
                 printf("Partita salvata!\n");
            else
                 printf("Errore salvataggio!\n");
        }

        if (cmd == 4) {
            if (caricaPartita("partita.bin", &gioco))
                 printf("Partita caricata!\n");
            else
                 printf("Errore caricamento!\n");
        }
    }

    printf("\nPunteggio finale: %d\n", gioco.punteggio);
    distruggiStack(&gioco.stack);
    return 0;
}

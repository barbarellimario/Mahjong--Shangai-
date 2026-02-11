#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tessera.h"
#include "ListaTessere.h"
#include "Tavolo.h"


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


void stampaMenu() {
    puts("\n=== MAHJONG SOLITAIRE ===");
    puts("1. Nuova partita");
    puts("2. Mossa (rimuovi coppia)");
    puts("0. Esci");
    printf("> ");
}

int main() {

    Tavolo tavolo;
    ListaTessere lista = creaLista();

    bool partitaAttiva = false;
    int scelta;

    while (true) {

        stampaMenu();
        scanf("%d", &scelta);
        while (getchar() != '\n');

        switch (scelta) {

            case 1: {
                inizializzaTavolo(&tavolo);

                if (lista != NULL)
                    distruggiLista(&lista);

                lista = creaLista();
                creaTessereIniziali(&lista);

                distribuisciTessere(&tavolo, &lista);

                partitaAttiva = true;
                stampaTavolo(&tavolo);
                break;
            }

            case 2: {
                if (!partitaAttiva) {
                    printf("Nessuna partita attiva!\n");
                    break;
                }

                int x1, y1, x2, y2;
                printf("Inserisci coordinate prima tessera (riga colonna): ");
                scanf("%d%d", &x1, &y1);
                printf("Inserisci coordinate seconda tessera (riga colonna): ");
                scanf("%d%d", &x2, &y2);

                x1--; y1--;
                x2--; y2--;

                if (rimuoviCoppia(&tavolo, x1, y1, x2, y2)) {
                    printf("Coppia rimossa!\n");
                } else {
                    printf("Mossa non valida!\n");
                }

                stampaTavolo(&tavolo);
                break;
            }

            case 0:
                printf("Grazie per aver giocato!\n");
                distruggiLista(&lista);
                exit(0);

            default:
                printf("Comando non valido!\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tessera.h"
#include "ListaTessere.h"
#include "Tavolo.h"
#include "Stack.h"
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

/* Menu principale */
void stampaMenu() {
    puts("\n=== MAHJONG SOLITAIRE ===");
    puts("1. Nuova partita");
    puts("2. Mossa (rimuovi coppia)");
    puts("3. Undo ultima mossa");
    puts("0. Esci");
    printf("> ");
}


int main() {

    Tavolo tavolo;
    ListaTessere lista = creaLista();
    Stack stackMosse = creaStack();

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

                distruggiStack(&stackMosse);
                stackMosse = creaStack();

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

                    Mossa m;
                    m.x1 = x1; m.y1 = y1;
                    m.x2 = x2; m.y2 = y2;

                    push(&stackMosse, m);
                    printf("Coppia rimossa!\n");
                } else {
                    printf("Mossa non valida!\n");
                }

                stampaTavolo(&tavolo);
                break;
            }

            case 3: {
                if (!partitaAttiva) {
                    printf("Nessuna partita attiva!\n");
                    break;
                }

                Mossa m;
                if (pop(&stackMosse, &m)) {
                    tavolo.celle[m.x1][m.y1]->rimossa = false;
                    tavolo.celle[m.x2][m.y2]->rimossa = false;
                    printf("Ultima mossa annullata.\n");
                } else {
                    printf("Nessuna mossa da annullare.\n");
                }

                stampaTavolo(&tavolo);
                break;
            }


            case 0:
                printf("Grazie per aver giocato!\n");
                distruggiLista(&lista);
                distruggiStack(&stackMosse);
                exit(0);

            default:
                printf("Comando non valido!\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tavolo.h"

void inizializzaTavolo(Tavolo* t) {
    int i, j;
    for (i = 0; i < RIGHE; i++)
        for (j = 0; j < COLONNE; j++)
            t->celle[i][j] = NULL;
}

static Tessera* estraiDaLista(ListaTessere* lista) {
    if (*lista == NULL)
        return NULL;

    Nodo* temp = *lista;
    Tessera* t = temp->tessera;
    *lista = temp->next;
    free(temp);

    return t;
}

void distribuisciTessere(Tavolo* t, ListaTessere* lista) {
    srand(time(NULL));

    int i, j;
    for (i = 0; i < RIGHE; i++) {
        for (j = 0; j < COLONNE; j++) {

            int r, c;
            do {
                r = rand() % RIGHE;
                c = rand() % COLONNE;
            } while (t->celle[r][c] != NULL);

            t->celle[r][c] = estraiDaLista(lista);
        }
    }
}

void stampaTavolo(const Tavolo* t) {
    int i, j;

    printf("\n   ");

    for (j = 0; j < COLONNE; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    for (i = 0; i < RIGHE; i++) {

        printf(" %2d ", i + 1);

        for (j = 0; j < COLONNE; j++) {
            if (t->celle[i][j] == NULL || t->celle[i][j]->rimossa)
                printf("   ");
            else
                stampaTessera(t->celle[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

bool tesseraLibera(const Tavolo* t, int x, int y) {
    if (t->celle[x][y] == NULL || t->celle[x][y]->rimossa)
        return false;

    /* lato sinistro libero */
    if (y == 0 || t->celle[x][y - 1] == NULL || t->celle[x][y - 1]->rimossa)
        return true;

    /* lato destro libero */
    if (y == COLONNE - 1 || t->celle[x][y + 1] == NULL || t->celle[x][y + 1]->rimossa)
        return true;

    return false;
}

bool rimuoviCoppia(Tavolo* t, int x1, int y1, int x2, int y2) {

    Tessera* t1 = t->celle[x1][y1];
    Tessera* t2 = t->celle[x2][y2];

    if (!tesseraLibera(t, x1, y1) || !tesseraLibera(t, x2, y2))
        return false;

    if (!tessereUguali(t1, t2))
        return false;

    t1->rimossa = true;
    t2->rimossa = true;

    return true;
}


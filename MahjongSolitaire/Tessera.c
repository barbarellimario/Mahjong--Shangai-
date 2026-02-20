#include <stdio.h>
#include <stdlib.h>
#include "Tessera.h"
#include "Colori.h"

Tessera* creaTessera(TipoTessera tipo, int valore) {
    Tessera* t = (Tessera*)malloc(sizeof(Tessera));
    if (t != NULL) {
        t->tipo = tipo;
        t->valore = valore;
        t->rimossa = false;
    }
    return t;
}


void stampaTessera(const Tessera* t) {

    if (t == NULL || t->rimossa) {
        printf("     ");
        return;
    }

    char simbolo;
    const char* colore;

    switch (t->tipo) {
        case BAMBOO:
            simbolo = 'B';
            colore = VERDE;
            break;
        case CERCHI:
            simbolo = 'C';
            colore = BLU;
            break;
        case CARATTERI:
            simbolo = 'K';
            colore = ROSSO;
            break;
        default:
            simbolo = '?';
            colore = RESET;
    }

    printf("%s[%c%d] %s", colore, simbolo, t->valore, RESET);
}


bool tessereUguali(const Tessera* t1, const Tessera* t2) {
    if (t1 == NULL || t2 == NULL)
        return false;

    return (t1->tipo == t2->tipo &&
            t1->valore == t2->valore);
}


void distruggiTessera(Tessera* t) {
    if (t != NULL)
        free(t);
}


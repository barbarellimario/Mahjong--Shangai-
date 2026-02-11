#include <stdio.h>
#include <stdlib.h>
#include "Tessera.h"

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
        printf("   ");
        return;
    }

    char simbolo;
    switch (t->tipo) {
        case BAMBOO: simbolo = 'B'; break;
        case CERCHI: simbolo = 'C'; break;
        case CARATTERI: simbolo = 'K'; break;
        default: simbolo = '?';
    }

    printf("%c%d ", simbolo, t->valore);
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


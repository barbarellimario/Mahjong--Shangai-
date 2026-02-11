#include <stdio.h>
#include <stdlib.h>
#include "ListaTessere.h"

ListaTessere creaLista() {
    return NULL;
}

bool listaVuota(ListaTessere l) {
    return (l == NULL);
}

bool inserisciInTesta(ListaTessere* l, Tessera* t) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovo == NULL)
        return false;

    nuovo->tessera = t;
    nuovo->next = *l;
    *l = nuovo;

    return true;
}

int lunghezzaLista(ListaTessere l) {
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->next;
    }
    return count;
}

void stampaLista(ListaTessere l) {
    while (l != NULL) {
        stampaTessera(l->tessera);
        printf("\n");
        l = l->next;
    }
}

void distruggiLista(ListaTessere* l) {
    Nodo* curr = *l;
    while (curr != NULL) {
        Nodo* tmp = curr;
        curr = curr->next;

        distruggiTessera(tmp->tessera);
        free(tmp);
    }
    *l = NULL;
}


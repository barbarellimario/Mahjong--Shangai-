#ifndef LISTATESSERE_H_INCLUDED
#define LISTATESSERE_H_INCLUDED
#include <stdbool.h>
#include "Tessera.h"


typedef struct nodo {
    Tessera* tessera;
    struct nodo* next;
} Nodo;


typedef Nodo* ListaTessere;


ListaTessere creaLista();
bool listaVuota(ListaTessere l);

bool inserisciInTesta(ListaTessere* l, Tessera* t);
int lunghezzaLista(ListaTessere l);

void stampaLista(ListaTessere l);
void distruggiLista(ListaTessere* l);


#endif // LISTATESSERE_H_INCLUDED

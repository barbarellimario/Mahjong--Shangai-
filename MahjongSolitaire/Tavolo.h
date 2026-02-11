#ifndef TAVOLO_H_INCLUDED
#define TAVOLO_H_INCLUDED
#include <stdbool.h>
#include "Tessera.h"
#include "ListaTessere.h"

#define RIGHE 8
#define COLONNE 8

typedef struct {
    Tessera* celle[RIGHE][COLONNE];
} Tavolo;

void inizializzaTavolo(Tavolo* t);
void distribuisciTessere(Tavolo* t, ListaTessere* lista);
void stampaTavolo(const Tavolo* t);

bool tesseraLibera(const Tavolo* t, int x, int y);
bool rimuoviCoppia(Tavolo* t, int x1, int y1, int x2, int y2);


#endif // TAVOLO_H_INCLUDED

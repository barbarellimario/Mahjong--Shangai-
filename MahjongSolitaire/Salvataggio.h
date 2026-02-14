#ifndef SALVATAGGIO_H_INCLUDED
#define SALVATAGGIO_H_INCLUDED
#include "Tavolo.h"
#include "Stack.h"
#include <stdbool.h>
#define RIGHE 8
#define COLONNE 8

bool salvaPartita(const char* filename, Tavolo* t, Stack s);
bool caricaPartita(const char* filename, Tavolo* t, Stack* s);


#endif // SALVATAGGIO_H_INCLUDED

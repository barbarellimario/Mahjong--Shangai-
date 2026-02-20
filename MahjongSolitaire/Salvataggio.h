#ifndef SALVATAGGIO_H_INCLUDED
#define SALVATAGGIO_H_INCLUDED
#include "Gioco.h"
#include <stdbool.h>

bool salvaPartita(const char* filename, Gioco* g);
bool caricaPartita(const char* filename, Gioco* g);


#endif // SALVATAGGIO_H_INCLUDED

#ifndef TESSERA_H_INCLUDED
#define TESSERA_H_INCLUDED
#include <stdbool.h>


typedef enum {
    BAMBOO,
    CERCHI,
    CARATTERI
} TipoTessera;


typedef struct {
    TipoTessera tipo;
    int valore;      // 1 - 9
    bool rimossa;
} Tessera;


Tessera* creaTessera(TipoTessera tipo, int valore);
void stampaTessera(const Tessera* t);
bool tessereUguali(const Tessera* t1, const Tessera* t2);
void distruggiTessera(Tessera* t);


#endif // TESSERA_H_INCLUDED

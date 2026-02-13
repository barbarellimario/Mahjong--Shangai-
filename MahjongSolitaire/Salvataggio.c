#include "Salvataggio.h"
#include <stdio.h>
#define DIM 10


bool salvaPartita(const char* filename, Tavolo* tavolo, Stack stack) {
    FILE* f = fopen(filename, "wb");
    if (!f) return false;

    fwrite(tavolo->celle, sizeof(Tessera*), DIM*DIM, f);

    Stack temp = stack;
    while (temp != NULL) {
        fwrite(&temp->mossa, sizeof(Mossa), 1, f);
        temp = temp->next;
    }

    fclose(f);
    return true;
}


bool caricaPartita(const char* filename, Tavolo* tavolo, Stack* stack) {
    FILE* f = fopen(filename, "rb");
    if (!f) return false;

    fread(tavolo->celle, sizeof(Tessera*), DIM*DIM, f);

    distruggiStack(stack);
    *stack = creaStack();

    Mossa mosse[500];
    int count = 0;
    while (fread(&mosse[count], sizeof(Mossa), 1, f) == 1) {
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {
        push(stack, mosse[i]);
    }

    fclose(f);
    return true;
}


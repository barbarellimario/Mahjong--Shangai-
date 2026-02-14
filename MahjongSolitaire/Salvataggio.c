#include "Salvataggio.h"
#include <stdio.h>
#include <stdlib.h>

bool salvaPartita(const char* filename, Tavolo* tavolo, Stack stack) {
    FILE* f = fopen(filename, "wb");
    if (!f) return false;

    for (int i = 0; i < RIGHE; i++) {
    for (int j = 0; j < COLONNE; j++) {

        bool esiste = (tavolo->celle[i][j] != NULL);
        fwrite(&esiste, sizeof(bool), 1, f);

        if (esiste) {
            fwrite(tavolo->celle[i][j], sizeof(Tessera), 1, f);
        }
    }
}

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

    for (int i = 0; i < RIGHE; i++) {
    for (int j = 0; j < COLONNE; j++) {

        bool esiste;
        fread(&esiste, sizeof(bool), 1, f);

        if (esiste) {
            tavolo->celle[i][j] = malloc(sizeof(Tessera));
            fread(tavolo->celle[i][j], sizeof(Tessera), 1, f);
        } else {
            tavolo->celle[i][j] = NULL;
        }
    }
}

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


#include "Salvataggio.h"
#include <stdio.h>
#include <stdlib.h>

bool salvaPartita(const char* filename, Gioco* g) {

    FILE* f = fopen(filename, "wb");
    if (!f) return false;


    fwrite(&g->punteggio, sizeof(int), 1, f);
    fwrite(&g->combo, sizeof(int), 1, f);
    fwrite(&g->modalita, sizeof(Modalita), 1, f);

    int tempo = tempoTrascorso(g);
    fwrite(&tempo, sizeof(int), 1, f);


    for (int i = 0; i < RIGHE; i++) {
        for (int j = 0; j < COLONNE; j++) {

            bool esiste = (g->tavolo.celle[i][j] != NULL);
            fwrite(&esiste, sizeof(bool), 1, f);

            if (esiste) {
                fwrite(&g->tavolo.celle[i][j]->tipo, sizeof(TipoTessera), 1, f);
                fwrite(&g->tavolo.celle[i][j]->valore, sizeof(int), 1, f);
                fwrite(&g->tavolo.celle[i][j]->rimossa, sizeof(bool), 1, f);
            }
        }
    }


    Stack temp = g->stack;
    while (temp != NULL) {
        fwrite(&temp->mossa, sizeof(Mossa), 1, f);
        temp = temp->next;
    }

    fclose(f);
    return true;
}


bool caricaPartita(const char* filename, Gioco* g) {

    FILE* f = fopen(filename, "rb");
    if (!f) return false;


    fread(&g->punteggio, sizeof(int), 1, f);
    fread(&g->combo, sizeof(int), 1, f);
    fread(&g->modalita, sizeof(Modalita), 1, f);

    int tempoSalvato;
    fread(&tempoSalvato, sizeof(int), 1, f);

    g->inizio = time(NULL) - tempoSalvato;

    inizializzaTavolo(&g->tavolo);

    for (int i = 0; i < RIGHE; i++) {
        for (int j = 0; j < COLONNE; j++) {

            bool esiste;
            fread(&esiste, sizeof(bool), 1, f);

            if (esiste) {

                TipoTessera tipo;
                int valore;
                bool rimossa;

                fread(&tipo, sizeof(TipoTessera), 1, f);
                fread(&valore, sizeof(int), 1, f);
                fread(&rimossa, sizeof(bool), 1, f);

                Tessera* t = creaTessera(tipo, valore);
                t->rimossa = rimossa;

                g->tavolo.celle[i][j] = t;

            } else {
                g->tavolo.celle[i][j] = NULL;
            }
        }
    }


    distruggiStack(&g->stack);
    g->stack = creaStack();

    Mossa mosse[500];
    int count = 0;

    while (fread(&mosse[count], sizeof(Mossa), 1, f) == 1)
        count++;

    for (int i = count - 1; i >= 0; i--)
        push(&g->stack, mosse[i]);

    fclose(f);
    return true;
}


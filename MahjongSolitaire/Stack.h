#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>

typedef struct {
    int x1, y1;
    int x2, y2;
} Mossa;

typedef struct nodoStack {
    Mossa mossa;
    struct nodoStack* next;
} NodoStack;

typedef NodoStack* Stack;

Stack creaStack();
bool stackVuoto(Stack s);

bool push(Stack* s, Mossa m);
bool pop(Stack* s, Mossa* m);

void distruggiStack(Stack* s);


#endif // STACK_H_INCLUDED

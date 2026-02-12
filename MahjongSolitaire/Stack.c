#include <stdlib.h>
#include "Stack.h"

Stack creaStack() {
    return NULL;
}

bool stackVuoto(Stack s) {
    return (s == NULL);
}

bool push(Stack* s, Mossa m) {
    NodoStack* nuovo = (NodoStack*)malloc(sizeof(NodoStack));
    if (nuovo == NULL)
        return false;

    nuovo->mossa = m;
    nuovo->next = *s;
    *s = nuovo;

    return true;
}

bool pop(Stack* s, Mossa* m) {
    if (stackVuoto(*s))
        return false;

    NodoStack* temp = *s;
    *m = temp->mossa;
    *s = temp->next;

    free(temp);
    return true;
}

void distruggiStack(Stack* s) {
    Mossa m;
    while (pop(s, &m));
}

//
// Created by erik on 2/07/22.
//

#ifndef HASHING_DYNAMIC_LIST_H
#define HASHING_DYNAMIC_LIST_H

#include "types.h"

typedef struct t_lista{
    PalabraType palabraType;
    struct t_lista *siguiente;  // puntero a siguiente
    struct t_lista *anterior;   // puntero a anterior
}NODO_LISTA, *P_NODO_LISTA;


Boolean listIsEmpty (P_NODO_LISTA list);

P_NODO_LISTA insertInList(P_NODO_LISTA lst, PalabraType palabraType, int pos);

P_NODO_LISTA deleteFromList(P_NODO_LISTA lst, int pos, PalabraType *palabraType);

P_NODO_LISTA searchInList(P_NODO_LISTA lst, char *palabra);

void print_list (P_NODO_LISTA lst);

#endif //HASHING_DYNAMIC_LIST_H

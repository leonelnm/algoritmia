//
// Created by erik on 2/07/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_list.h"

Boolean listIsEmpty (P_NODO_LISTA list){
    if(list==NULL)
        return TRUE;
    else
        return FALSE;
}

P_NODO_LISTA insertInList(P_NODO_LISTA lst, PalabraType palabraType, int pos){ // devuelve P_NODO_LISTA

    P_NODO_LISTA laux, lsgte;
    int i;

    if(pos < 1 ) {
        printf("ERROR, fuera de posicion\n");
        return lst;
    }
    //Insertamos al principio
    if ( pos == 1 || listIsEmpty(lst)){
        laux = (P_NODO_LISTA)malloc(sizeof(NODO_LISTA));
        laux->palabraType = palabraType;
        laux->anterior = NULL;  // Soy el primero, pongo el anterior a NULL
        laux->siguiente = lst;  // Y el siguiente lo apunto a lst
        if(!listIsEmpty(lst))
            lst->anterior = laux; // Si no es vacia apuntamos lst->anterior al primero

        return(laux);
    }

    // resto de posiciones
    for (i=1, laux=lst;(i<pos-1)&&(laux!=NULL);i++)
        laux = laux->siguiente;


    if( laux != NULL) {
        lsgte = laux->siguiente;
        laux->siguiente = (P_NODO_LISTA)malloc(sizeof(NODO_LISTA));
        laux->siguiente->palabraType = palabraType;
        laux->siguiente->siguiente = lsgte; // Apuntamos al siguiente
        laux->siguiente->anterior = laux;   // Apuntamos hacia atras

        if(lsgte != NULL) //no es el ultimo cuando inserto
            lsgte->anterior = laux->siguiente;
    } //fin del if
    else  printf("ERROR, fuera de posicion\n");

    return(lst);
}


P_NODO_LISTA deleteFromList(P_NODO_LISTA lst, int pos, PalabraType *palabraType){

    P_NODO_LISTA laux;
    int i;

    //Si la posicion esta fuera de rango o la lista es vacia nose hace nada. Devolvemos la lista tal cual.
    if ((pos < 1) || (listIsEmpty(lst))){
        printf("ERROR, Lista vacia o posicion no valida\n");
        palabraType = NULL;
        return lst;

    }

    // Primera posicion
    if (pos == 1){
        laux = lst->siguiente;
        *palabraType = lst->palabraType;
        free(lst);
        if(laux != NULL)
            laux->anterior = NULL;
        return (laux);
    }

    // Resto de posiciones
    for (i=1, laux=lst; (i<pos)&&(laux->siguiente != NULL); i++)
        laux = laux->siguiente;

    //Si no hemos llegado al �ltimo nodo, eliminamos y
    //actualizamos las referencias del nodo anterior y posterior del eliminado
    if(laux->siguiente != NULL) {
        laux->anterior->siguiente = laux->siguiente;
        laux->siguiente->anterior = laux->anterior;
        *palabraType = laux->palabraType;
        free(laux);
    }
    else if (pos==i){ //es el ultimo de la lista
        laux->anterior->siguiente=laux->siguiente; //null
        *palabraType = laux->palabraType;
        free(laux);
    }
    else {
        palabraType = NULL;
        printf("ERROR, fuera de posicion\n");
    }

    return(lst);

}

P_NODO_LISTA searchInList(P_NODO_LISTA lst, char *palabra){

    P_NODO_LISTA laux;
    for(laux=lst; laux!=NULL;laux=laux->siguiente)
        if(strcmp(laux->palabraType.palabra, palabra) == 0) break;

    return(laux);
}

void print_list (P_NODO_LISTA lst){
    P_NODO_LISTA p;
    p=lst;
    printf("Valores dentro de lista:\n");
    while(p != NULL){
        printf("\t%s: %s (%d)\n", p->palabraType.filename, p->palabraType.palabra, p->palabraType.originalkey);
        p=p->siguiente;
    }
    printf("\n");
}

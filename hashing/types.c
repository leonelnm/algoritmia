//
// Created by erik on 15/06/22.
//

#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

PalabraType *createPalabraType(char *filename, char *palabra){
    PalabraType *pPalabraType = malloc(sizeof(PalabraType));

    // Must allocate memory for contents of pointers.  Here, strdup()
    // creates a new copy of name.  Another option:
    // p->name = malloc(strlen(name)+1);
    // strcpy(p->name, name);
    pPalabraType->filename = strdup(filename);
    pPalabraType->palabra = strdup(palabra);

    pPalabraType->finalkey = -1;
    pPalabraType->originalkey = -1;
    pPalabraType->attempts = -1;

    return pPalabraType;
}

void printTableHash(PalabraTypeTableHash *tableHash, int size){
    for (int i = 0; i < size; ++i) {
        printf("i(%d).%d\t",i, tableHash[i].status);
        if(i != 0 && i % 10 == 0){
            printf("\n");
        }
    }
}

int countRepeteadWord(PalabraType *list, char *filename, int size){
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        if(strcmp(filename, list[i].filename) == 0){
            counter++;
        }
    }

    return counter;
}
//
// Created by erik on 21/06/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

FileType *createFileType(char *filename, int nWords){
    FileType *ft = malloc(sizeof *ft);
    if(ft){
        ft->nWords = nWords;
        ft->filename = (char *)malloc(strlen(filename)+1 * sizeof(char));
        strcpy(ft->filename, filename);

        char order[] = "ordenado_";
        char *fullName = (char *)malloc((strlen(filename) + strlen(order)) + 1 * sizeof(char));
        strcat(fullName, order);
        strcat(fullName, filename);

        ft->filenameOrdered = (char *)malloc(strlen(fullName) * sizeof(char));
        strcpy(ft->filenameOrdered, fullName);
    }else{
        perror("No se reservar memoria para crear un FileType");
        return EXIT_FAILURE;
    }

    return ft;
}

void freeFileType(FileType *ft){
    free(ft->filename);
    for (int i = 0; i < ft->nWords; ++i) {
        free(ft->words[i]);
    }
    free(ft->words);
    free(ft);
}

char *getOrderType(int orderBy){
    char *order;
    if(orderBy == ASC){
        order = strdup("ASC [A-Z]");
    }else{
        order = strdup("DESC [Z-A]");
    }

    return order;
}
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
    }else{
        perror("No se reservar memoria para crear un FileType");
        return EXIT_FAILURE;
    }

    return ft;
}

void freeFileType(FileType *ft){
    free(ft->filename);
    free(ft->words);
    for (int i = 0; i < ft->nWords; ++i) {
        //free(ft->words[i]);
    }
    free(ft);
}

//
// Created by erik on 18/06/22.
//

#include "fileUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **readFile(FileType *fileType){
    int size = fileType->nWords;
    int wordLength = MAX_LENGTH;

    FILE *file = fopen(fileType->filename, "r");
    if (file == NULL) {
        printf("Error intentando leer el archivo: %s\n", fileType->filename);
        perror("ERROR: ");
        exit(EXIT_FAILURE);
    }

    char **words = malloc(sizeof(char *) * size);
    char line[wordLength]; // Para guardar la linea de cada fichero
    int index = 0;
    while (!feof(file)) {
        fscanf(file, "%s", line);
        words[index] = strdup(line);
        index++;
    }

    return words;
}

void writeFile(FileType *fileType){

    FILE* file;
    file = fopen(fileType->filenameOrdered, "wt");

    for (int i = 0; i < fileType->nWords; ++i) {
        fprintf(file, fileType->words[i]);
        if(i < fileType->nWords -1){
            fprintf(file, "\n");
        }
    }
    fclose(file);
}
//
// Created by erik on 18/06/22.
//

#include "fileUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **readFile(char *filename){
    int size = 10;
    int wordLength = 10;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error intentando leer el archivo: %s\n", filename);
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

void writeFile(char *filename, char **words){

}
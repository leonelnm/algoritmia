//
// Created by erik on 12/06/22.
//

#include "read_files.h"
#include <stdlib.h>
#include <string.h>

int countChars(char *filename){
    FILE* fp;
    int count = 0;
    char c;

    // Abrir archivo
    fp = fopen(filename, "r");
    // Existe
    if (fp == NULL) {
        printf("No se puede abrir archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (c = getc(fp); c != EOF; c = getc(fp)){
        count = count + 1;
    }

    fclose(fp);

    return count;
}

char *getDataFromFile(char *filename, int size){
    FILE* fp;
    char *text = malloc(sizeof(char) * size);

    // Abrir archivo
    fp = fopen(filename, "r");
    // Existe
    if (fp == NULL) {
        printf("No se puede abrir archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char c;
    while ((c= getc(fp)) != EOF){
        text[i]=c;
        i++;
    }

    fclose(fp);
    return text;

}
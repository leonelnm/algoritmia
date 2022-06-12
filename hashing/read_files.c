//
// Created by erik on 12/06/22.
//

#include "read_files.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int countWordsInFIle(FILE *file, int *longestWord) {
    fseek(file, 0, SEEK_SET);

    char ch;
    int word_counter = 0;
    int word_length = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n' || ch == ' ') {
            word_counter++;

            if(*longestWord < word_length) *longestWord = word_length;

            word_length = 0;
        }
        word_length++;
    }

    printf("Cantidad de palabras -> %d\n", word_counter);

    fseek(file, 0, SEEK_SET);
    return word_counter > 0 ? word_counter + 1 : 0;
}


PalabraType *getDataFromFile(char *filename, int *listSize) {
    printf("Leyendo archivo %s...\n", filename);
    char *path = malloc(sizeof(char*) * ( strlen(filename) + 6)); // 5 = docs/
    strcpy(path, "docs/");
    strcat(path, filename);
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Error intentando leer el archivo: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int longestWord = 0;
    int size = countWordsInFIle(file, &longestWord);
    *listSize = size;

    printf("Valor palabra más larga: %d\n", longestWord);

    PalabraType *palabrasType_lista = (PalabraType *) malloc(sizeof(PalabraType) * size);
    if(palabrasType_lista == NULL){
        perror("No se puede asignar memoria para leer el archivo");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    char line[longestWord];
    while (!feof(file)) {
        fscanf(file, "%s", line);
        if(line){
            PalabraType palabraType;
            palabraType.filename = filename;
            palabraType.palabra = strdup(line);
            palabrasType_lista[index] = palabraType;
            index++;
        }
    }



    fclose(file);
    return palabrasType_lista;
}

char **getFilenamesList(int *listSize){

    DIR *directory;
    struct dirent *dir;
    directory = opendir("docs/");

    if (directory){
        // 1. Contar cantidad de archivos .txt
        int amountTxt = 0;
        printf("Archivos encontrados: ");
        while ((dir = readdir(directory)) != NULL)
        {
            int len = strlen(dir->d_name);
            char filename[len];
            strcpy(filename, dir->d_name);
            if(strcmp(".txt", &filename[len-4]) == 0){
                amountTxt++;
                printf("%s, ", filename);
            }
        }

        // 2. Mover el puntero al inicio del directorio
        rewinddir(directory);
        // 3. Crear array para añadir todos los nombres de archivos
        *listSize = amountTxt;
        char **docsTxt = malloc(sizeof(char*) * amountTxt);
        int index = 0;
        while ((dir = readdir(directory)) != NULL){

            int len = strlen(dir->d_name);
            char filename[len];
            strcpy(filename, dir->d_name);
            if(strcmp(".txt", &filename[len-4]) == 0){
                docsTxt[index] = malloc(sizeof(char*) * strlen(filename)+1);
                strcpy(docsTxt[index], filename);
                index++;
            }
        }

        closedir(directory);
        printf("\n");
        return docsTxt;
    }else{
        printf("ERROR, imposible encontrar archivos en docs/");
        exit(EXIT_FAILURE);
    }
}
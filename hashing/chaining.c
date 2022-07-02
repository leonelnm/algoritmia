//
// Created by erik on 2/07/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "read_files.h"
#include "dynamic_list.h"
#include "chaining.h"

int showChainingMenu(int firstTime){
    if(firstTime == TRUE){
        printf("\n\n");
        printf("*** Hashing Dependiente de Clave ***");
    }
    printf("\n\t1. Buscar palabra\n");
    printf("\t2. Regresar\n");
    printf("\t0. Salir\n");
    printf("\nSeleccione opción: ");

    int optionSelected = -1;
    scanf("%d", &optionSelected);
    while(isValidOption(optionSelected, 0, 2) != TRUE){
        scanf("%d", &optionSelected);
    }

    return optionSelected;
}

int executeChaining(char **filename_list, int filenamelistSize){

    if(filenamelistSize <= 0){
        printf("No hay archivos para leer\n");
        return EXIT;
    }
    int size = getLengthFIle(filename_list[0]);
    P_NODO_LISTA *list = loadDataOnList(filename_list, filenamelistSize, size);
    if(list == NULL){
        perror("No se ha inicializado la list\n");
        exit(EXIT_FAILURE);
    }

    int option = showChainingMenu(TRUE);
    char word[50];
    P_NODO_LISTA listSearch = NULL;
    while (option != EXIT && option != RETURN){
        while(1){
            printf("\nInserte palabra a buscar (QUIT para terminar) :");
            scanf("%s", word);

            if(strcmp("QUIT", word) == 0) break;

            int h = H(getAsciiValueFromString(word), size);

            listSearch = searchInList(list[h], word);

            if(listSearch == NULL){
                printf("No se ha encontrado la palabra: %s\n", word);
            }else{
                showResponse(listSearch, word, filename_list, filenamelistSize);
            }
        }
        option = showChainingMenu(FALSE);
    }

    free(list);
    return option;
}

P_NODO_LISTA *loadDataOnList(char **filename_list, int filenamelistSize, int size){
    printf("Cargando palabras en lista\n");
    P_NODO_LISTA *list = (P_NODO_LISTA *) malloc(size * sizeof(NODO_LISTA));
    if(list == NULL){
        perror("No se ha podido reservar memoria para lista\n");
        exit(EXIT_FAILURE);
    }
    // inicializar cada lista a NULL
    for (int i = 0; i < size; ++i) {
        list[i] = NULL;
    }

    int h;
    for (int i = 0; i < filenamelistSize; ++i) {
        int dataListSize = 0;
        // Leer palabras de archivo
        PalabraType *data = getDataFromFile(filename_list[i], &dataListSize);

        for (int j = 0; j < dataListSize; ++j) {
            if(data[j].filename != NULL && data[j].palabra != NULL){
                h = H(getAsciiValueFromString(data[j].palabra), size);
                data[j].originalkey = h;
                list[h] = insertInList(list[h], data[j], 1);
            }
        }

    }
    printf("Ready!\n");

    return list;
}

int countRepetedWordsOnList(P_NODO_LISTA list, char *filename, char *word) {
    int counter = 0;

    P_NODO_LISTA laux;
    for (laux = list; laux != NULL; laux = laux->siguiente)
        if (strcmp(laux->palabraType.palabra, word) == 0
            && strcmp(laux->palabraType.filename, filename) == 0) {
            counter++;
        }

    return counter;
}

void showResponse(P_NODO_LISTA list, char *word, char **filename_list, int filenamelistSize){
    printf("\nRespuesta:\n");
    ResponseSearch responses[filenamelistSize];
    for (int i = 0; i < filenamelistSize; ++i) {
        ResponseSearch search;
        search.filename = filename_list[i];
        search.repeated = countRepetedWordsOnList(list, filename_list[i], word);
        responses[i] = search;
    }

    for (int i = 0; i < filenamelistSize; ++i) {
        if(responses[i].repeated > 0){
            printf("Número palabras ('%s', %s) = %d\n", word, responses[i].filename, responses[i].repeated);
        }
    }

    // Aplicando Burbuja
    ResponseSearch temp;
    for (int i = 0; i < filenamelistSize-1; i++) {
        for (int j = i+1; j < filenamelistSize; j++) {
            if(responses[i].repeated < responses[j].repeated) {
                memcpy(&temp, &responses[i], sizeof(ResponseSearch));
                memcpy(&responses[i], &responses[j], sizeof(ResponseSearch));
                memcpy(&responses[j], &temp, sizeof(ResponseSearch));
            }
        }
    }

    printf("Por tanto: ");
    for (int i = 0; i < filenamelistSize; ++i) {
        if(responses[i].repeated > 0){
            printf("%s", responses[i].filename);

            if(i < filenamelistSize-1){
                if(responses[i].repeated == responses[i+1].repeated) printf("\t=\t");
                else if(responses[i+1].repeated > 0) printf("\t>\t");
            }

        }
    }

    printf("\n");

}
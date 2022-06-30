//
// Created by erik on 18/06/22.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "burbuja.h"
#include "fileUtils.h"

void executeBurbuja(FileType **fileTypes, int orderBy){

    printf("\n**** INICIO Algoritmo Burbuja ****\n");
    printf("Tipo de ordenación seleccionada: %s\n", getOrderType(orderBy));

    FileType *ftSelected;

    for (int i = 0; i < N_FILES; ++i) {
        ftSelected = fileTypes[i];
        ftSelected->words = readFile(ftSelected);
        orderByBurbuja(ftSelected, orderBy);
        writeFile(ftSelected);
    }

    printf("\n**** FIN Algoritmo Burbuja ****\n");

}

void orderByBurbuja(FileType *fileType, int orderBy){

    printf("\nOrdenando fichero %s\n", fileType->filename);
    int size = fileType->nWords;

    char tmp[MAX_LENGTH];
    int nSwap = 0;
    int nComparations = 0;

    clock_t start, end;
    double cpu_time_used;

    if(orderBy == ASC){
        start = clock();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if(strcmp(fileType->words[i], fileType->words[j]) < 0) {
                    strcpy(tmp, fileType->words[i]);
                    strcpy(fileType->words[i], fileType->words[j]);
                    strcpy(fileType->words[j], tmp);
                    nSwap++;
                }
                nComparations++;
            }
        }
        end = clock();
    }else{
        start = clock();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if(strcmp(fileType->words[i], fileType->words[j]) > 0) {
                    strcpy(tmp, fileType->words[i]);
                    strcpy(fileType->words[i], fileType->words[j]);
                    strcpy(fileType->words[j], tmp);
                    nSwap++;
                }
                nComparations++;
            }
        }
        end = clock();
    }

    cpu_time_used = ((double) (end - start)) *1000 / CLOCKS_PER_SEC;
    printf("Tiempo %.3f ms\n", cpu_time_used);

    printf("Numero de comparaciones: %d\n", nComparations);
    printf("Numero de intercambios: %d\n", nSwap);
}

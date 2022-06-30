//
// Created by erik on 25/06/22.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdatomic.h>
#include "quickSort.h"
#include "fileUtils.h"

atomic_int nSwap;

void executeQuickSort(FileType **fileTypes, int orderBy){
    printf("\n**** INICIO Algoritmo QuickSort ****\n");
    printf("Tipo de ordenación seleccionada: %s\n", getOrderType(orderBy));

    FileType *ftSelected;

    for (int i = 0; i < N_FILES; ++i) {
        ftSelected = fileTypes[i];
        ftSelected->words = readFile(ftSelected);
        printf("\nOrdenando fichero %s\n", ftSelected->filename);
        orderByQuickSort(ftSelected, 0, ftSelected->nWords -1, orderBy, FALSE);
        writeFile(ftSelected);
    }

    printf("\n**** FIN Algoritmo QuickSort ****\n");
}

void swap(char **a, char **b){
    char *tmp = *a;
    *a = *b;
    *b = tmp;

    nSwap++;
}

void orderByQuickSort(FileType *fileType, int ini, int end, int orderBy, Boolean isRecursive){
    // Contadores para mostrar calculos solicitados
    clock_t startTime, endTime;
    double cpu_time_used;

    // Constantes de QuickSort
    char *pivote;
    int i,j;

    if(isRecursive != TRUE){
        startTime = clock();
    }
    // Caso lista con 1 solo elemento --> No hacer nada
    if(ini >= end) return;

    // Caso lista con 2 elementos --> Comprobar si es necesario ordenarlos
    if(ini+1 == end){
        if(orderBy == ASC){
            if(strcmp(fileType->words[ini], fileType->words[end]) > 0){
                // No están ordenados los dos números, intercambiar
                swap(&(fileType->words[ini]), &(fileType->words[end]));
            }
        }else{
            if(strcmp(fileType->words[ini], fileType->words[end]) < 0){
                // No están ordenados los dos números, intercambiar
                swap(&(fileType->words[ini]), &(fileType->words[end]));
            }
        }
        return;
    }

    // Pivote --> La posición del centro de la lista
    int medio = (ini+end)/2;

    // Intercambiar pivote por el último elemento
    swap(&(fileType->words[medio]), &(fileType->words[end]));
    pivote=fileType->words[end];

    for(i=ini, j=end-1; ; ){
        if(orderBy == ASC){
            while((i <= end-1) && (strcmp(fileType->words[i], pivote) < 0)) i++;
            while((j >= ini) && (strcmp(pivote, fileType->words[j]) < 0)) j--;
        }else{
            while((i <= end-1) && (strcmp(fileType->words[i], pivote) > 0)) i++;
            while((j >= ini) && (strcmp(pivote, fileType->words[j]) > 0)) j--;
        }

        if(i<j){  // Todavía no se han intercambiado los índices, intercambiar números
            swap(&(fileType->words[i]), &(fileType->words[j]));
            i++; j--;
        }else // Se han intercambiando los índices, fin de la particion
            break;
    }

    //colocación del pivote en su sitio
    swap(&(fileType->words[i]), &(fileType->words[end]));
    //termina particion de la lista;
    // llamadas recursivas
    orderByQuickSort(fileType, ini, i-1, orderBy, TRUE);  // Vector de la izquierda del pivote
    orderByQuickSort(fileType, i+1, end, orderBy, TRUE);  // Vector de la derecha del pivote

    if(isRecursive != TRUE) {
        endTime = clock();
        cpu_time_used = ((double) (endTime - startTime)) * 1000 / CLOCKS_PER_SEC;
        printf("Tiempo %.3f ms\n", cpu_time_used);
        printf("Numero de intercambios: %d\n", nSwap);
    }
}
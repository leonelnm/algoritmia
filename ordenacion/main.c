#include <stdio.h>
#include "types.h"
#include "burbuja.h"
#include "quickSort.h"

int showMenu(Option option, Boolean showHeader);

int main() {

    int algorithmSelected = -1;
    int orderBy = -1;
    int readFirstTime = FALSE;

    FileType *fileTypes[N_FILES];

    while(algorithmSelected != EXIT && orderBy != EXIT){
        algorithmSelected = showMenu(ALGORITHM, TRUE);
        //algorithmSelected = QUICKSORT;
        if(algorithmSelected == EXIT) break;

        orderBy = showMenu(ORDERBY, FALSE);
        //orderBy = ASC;
        if(orderBy == EXIT) break;

        if(readFirstTime != TRUE){
            fileTypes[0]=createFileType("words1000.txt", 1000);
            fileTypes[1]=createFileType("words2000.txt", 2000);
            fileTypes[2]=createFileType("words5000.txt", 5000);
            printf("archivos leidos!\n");
            readFirstTime = TRUE;
        }

        if(BURBUJA == algorithmSelected){
            executeBurbuja(fileTypes, orderBy);
        }

        if(QUICKSORT == algorithmSelected){
            executeQuickSort(fileTypes, orderBy);
        }
        //orderBy = EXIT;
    }

    for (int i = 0; i < N_FILES; ++i) {
        freeFileType(fileTypes[i]);
    }

    printf("Bye :)\n");

    return 0;
}

int showMenu(Option option, Boolean showHeader){
    int selected = -1;

    if(showHeader == TRUE){
        printf("\n************************************\n");
    }

    if(ALGORITHM == option){
        printf("***** Algoritmos de Ordenación *****\n");
        printf("\t1. Burbuja\n");
        printf("\t2. QuickSort\n");
    }

    if(ORDERBY == option){
        printf("Seleccionar orden a aplicar\n");
        printf("\t1. Ascendente [A-Z]\n");
        printf("\t2. Descendente [Z-A]\n");
    }

    printf("\t0. Salir\n");
    printf("\nInserte opcion: ");
    scanf("%d", &selected);

    while(selected < 0 || selected >2){
        printf("Inserte opción entre [0-2]\n");
        scanf("%d", &selected);
    }

    return selected;
}
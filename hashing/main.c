#include <stdio.h>
#include <stdlib.h>
#include "read_files.h"
#include "key_dependent.h"
#include "chaining.h"

int showMainMenu();

int main() {

    printf("Cargando...\n");
    // Buscar archivos txt
    printf("Buscando archivos .txt en docs/ ...\n");
    int filenamelistSize = 0;
    char **filename_list = getFilenamesList(&filenamelistSize);

    if (filenamelistSize == 0) {
        perror("No se han encontrado archivos .txt en docs/");
        exit(EXIT_FAILURE);
    }

    //executeChaining(filename_list, filenamelistSize);

    int option = showMainMenu();
    int response = -1;
    //int option = EXIT;
    while (option != EXIT){
        if(option == 1){    // Dependiente de Clave
            response = executeKeyDependent(filename_list, filenamelistSize);
        }
        if(option == 2){ // Encadenamiento
            response = executeChaining(filename_list, filenamelistSize);
        }

        if(response == EXIT) break;

        option = showMainMenu();
    }

    printf("\nBye! :)\n");
    free(filename_list);
    return 0;
}

int showMainMenu(){
    printf("\n\n\n\n");
    printf("*********************************************\n");
    printf("*** Hashing: Técnicas resolver colisiones ***\n");
    printf("\t1. Dependiente de clave\n");
    printf("\t2. Encadenamiento\n");
    printf("\t0. Salir\n");
    printf("\nSeleccione opción: ");

    int optionSelected = -1;
    scanf("%d", &optionSelected);
    while(isValidOption(optionSelected, 0, 2) != TRUE){
        scanf("%d", &optionSelected);
    }

    return optionSelected;
}

#include <stdio.h>
#include <stdlib.h>
#include "read_files.h"

void showMainMenu(int firstTime);

int main() {

    // Buscar archivos txt
    printf("Buscando archivos .txt en docs/ ...\n");
    int filenamelistSize = 0;
    char **filename_list = getFilenamesList(&filenamelistSize);

    if (filenamelistSize == 0) {
        perror("No se han encontrado archivos .txt en docs/");
        exit(EXIT_FAILURE);
    }

    // Crear tabla hash a null
    int sizeTableHash = 0;
    PalabraTypeTableHash *tableHash = NULL;

    for (int i = 0; i < filenamelistSize; ++i) {
        printf("\n");
        int dataListSize = 0;
        // Leer palabras de archivo
        PalabraType *data = getDataFromFile(filename_list[i], &dataListSize);
        //printPalabraType(data, dataListSize);

        // Inicializar tableHash
        sizeTableHash = dataListSize;
        tableHash = init(tableHash, &sizeTableHash);

        for (int j = 0; j < dataListSize+1; ++j) {
            if(data[j].filename != NULL && data[j].palabra != NULL){
                int inserted = insert(tableHash, data[j], sizeTableHash, FALSE);
                //printTableHash(tableHash, sizeTableHash);
                // Si no ha insertado O el factor de carga es mayor a CLOUDY_LOAD_FACTOR
                if(inserted != TRUE
                    || isLoadFactorCloudy(tableHash, sizeTableHash) == TRUE){
                    tableHash = resizeTable(tableHash, &sizeTableHash);
                    j--;
                }
            }
        }
        printf("\n***** Tabla %s *****\n", filename_list[i]);
        printTableHash(tableHash, sizeTableHash);
    }

    showMainMenu(TRUE);
    int optionSelected = -1;
    scanf("%d", &optionSelected);

    while (1)
    {
        if(optionSelected == 0){
            break;
        }
        if(optionSelected < 0 || optionSelected > 1){
            printf("\nInserte opción válida 0-1: ");
            scanf("%d", &optionSelected);
        }

        if(optionSelected == 1 ){
            char cadena[50];
            int counterFounds = 0;
            printf("\nInserte palabra a buscar: ");
            scanf("%s", cadena);
            PalabraType *response = search(tableHash, cadena, sizeTableHash, &counterFounds);
            if(response == NULL){
                printf("\nNo se ha encontrado la palabra insertada!\n");
            }

            if(counterFounds > 0){
                printf("\nRespuesta:\n");
                ResponseSearch responses[filenamelistSize];
                for (int i = 0; i < filenamelistSize; ++i) {
                    ResponseSearch search;
                    search.filename = filename_list[i];
                    search.repeated = countRepeteadWord(response, filename_list[i], counterFounds);

                    responses[i] = search;
                }

                for (int i = 0; i < filenamelistSize; ++i) {
                    if(responses[i].repeated > 0){
                        printf("Número palabras ('%s', %s)=%d\n", cadena, responses[i].filename, responses[i].repeated);
                    }
                }
            }

        }

    }

    printf("\nBye! :)\n");
    free(filename_list);
    free(tableHash);
    return 0;
}

void showMainMenu(int firstTime){
    printf("\n\n**********************************\n");
    printf("***Hashing Dependiente de Clave***\n");
    printf("1. Buscar palabra\n");
    printf("0. Salir\n");
    printf("Seleccione opción: ");
}

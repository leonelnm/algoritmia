//
// Created by erik on 2/07/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "read_files.h"
#include "key_dependent.h"

int showMenu(int firstTime){
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

int executeKeyDependent(char **filename_list, int filenamelistSize){
    int sizeTableHash = 0;
    PalabraTypeTableHash *tableHash = loadData(filename_list, filenamelistSize, &sizeTableHash);

    if(tableHash == NULL){
        perror("Error al insertar datos en tabla hash (Dependiente de clave)");
        exit(EXIT_FAILURE);
    }

    int option = showMenu(TRUE);
    char word[50];
    int counterFounds = 0;
    while (option != EXIT && option != RETURN){
        while(1){
            printf("\nInserte palabra a buscar (QUIT para terminar) :");
            scanf("%s", word);
            if(strcmp("QUIT", word) == 0){
                break;
            }
            PalabraType *response = search(tableHash, word, sizeTableHash, &counterFounds);

            if(counterFounds == 0){
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
                        printf("Número palabras ('%s', %s)=%d\n", word, responses[i].filename, responses[i].repeated);
                    }
                }
            }
            counterFounds = 0;
        }
        option = showMenu(FALSE);
    }

    free(tableHash);

    return option;
}

PalabraTypeTableHash *loadData(char **filename_list, int filenamelistSize, int *responseSizeTable){
    printf("Cargando datos en tabla hash\n");
    int sizeTableHash = 0;
    PalabraTypeTableHash *tableHash = NULL;
    for (int i = 0; i < filenamelistSize; ++i) {
        int dataListSize = 0;
        // Leer palabras de archivo
        PalabraType *data = getDataFromFile(filename_list[i], &dataListSize);
        //printArrayPalabraType(data, dataListSize);
        //printTableHash(tableHash, sizeTableHash);

        // Inicializar tableHash
        sizeTableHash = dataListSize;
        tableHash = init(tableHash, &sizeTableHash);

        for (int j = 0; j < dataListSize+1; ++j) {
            if(data[j].filename != NULL && data[j].palabra != NULL){
                int inserted = insert(tableHash, data[j], sizeTableHash, FALSE);
                // Si no ha insertado O el factor de carga es mayor a CLOUDY_LOAD_FACTOR
                if(inserted != TRUE
                   || isLoadFactorCloudy(tableHash, sizeTableHash) == TRUE){
                    tableHash = resizeTable(tableHash, &sizeTableHash);
                    j--;
                }
            }
        }

    }

    *responseSizeTable = sizeTableHash;
    printf("\nready!");
    return tableHash;
}

PalabraTypeTableHash *init(PalabraTypeTableHash *tableHash, int *size) {
    int currentSize = *size;

    if (tableHash == NULL) {
        if( currentSize % 2 == 0){
            currentSize++;
            *size = currentSize;
        }
        tableHash = (PalabraTypeTableHash *) malloc(sizeof(PalabraTypeTableHash) * currentSize);

        for (int i = 0; i < currentSize; i++) {
            tableHash[i].status = LIBRE;
        }
    }
    return tableHash;
}

PalabraTypeTableHash *resizeTable(PalabraTypeTableHash *tableHash, int *currentSize) {
    int elementsInserted = 0;
    int size = *currentSize;

    for (int i = 0; i < size; ++i) {
        if (tableHash[i].status != LIBRE) {
            elementsInserted++;
        }
    }

    if (elementsInserted > 0) {
        PalabraTypeTableHash *tmpBeforeReinitTable = (PalabraTypeTableHash *) malloc(
                sizeof(PalabraTypeTableHash) * elementsInserted);
        int j = 0;
        for (int i = 0; i < size; ++i) {
            if (tableHash[i].status != LIBRE) {
                tmpBeforeReinitTable[j] = tableHash[i];
                j++;
            }
        }
        int newSize = size * 2;
        if(newSize % 2 == 0){
            newSize++;
        }
        //printf("Nuevo tamaño: %d\n", newSize);
        PalabraTypeTableHash *tmp = realloc(tableHash, sizeof(PalabraTypeTableHash) * newSize);
        if (tmp) {
            tableHash = tmp;
            for (int i = 0; i < newSize; ++i) {
                tableHash[i].status = LIBRE;
            }
        } else {
            perror("No se puede redimensionar la tabla");
            exit(EXIT_FAILURE);
        }

        // Volver a insertar los valores
        for (int i = 0; i < elementsInserted; ++i) {
            insert(tableHash, tmpBeforeReinitTable[i].palabraType, newSize, TRUE);
        }

        *currentSize = newSize;
    }

    return tableHash;
}

int insert(PalabraTypeTableHash *tableHash, PalabraType palabraType, int size, int reinsert) {

    int inserted = FALSE;

    // Calcula key (k)
    int k = getAsciiValueFromString(palabraType.palabra);

    //printf("\ttableSize:%d   k:%d   ", size, k);
    // Obtiene h0
    int h0 = H(k, size);
    //printf("h0:%d\t", h0);

    // Crear el registro a insertar
    PalabraTypeTableHash reg;
    reg.status = OCUPADO;
    reg.palabraType = palabraType;
    reg.palabraType.originalkey = h0;

    int nCollisions = 0;
    if (isAvailable(tableHash[h0].status) == TRUE) {
        reg.palabraType.finalkey = h0;
        reg.palabraType.attempts = nCollisions;
        tableHash[h0] = reg;
        inserted = TRUE;

        //printf("\tOK!");
    } else {
        nCollisions = 1;
        int newH;
        while (inserted != TRUE) {
            //printf("\n\tcollision:%d   ", nCollisions);
            newH = G(k, nCollisions, size);
            //printf("newH:%d",newH);
            if (isAvailable(tableHash[newH].status) == TRUE) {
                reg.palabraType.finalkey = newH;
                reg.palabraType.attempts = nCollisions;
                tableHash[newH] = reg;
                inserted = TRUE;
                //printf("\tOK!");
            } else {
                nCollisions++;
                if (nCollisions > size) {
                    printf("\nNo se puede insertar la palabra %s, el número de colisiones es mayor que N_ELEMENTs, %d > %d\n",
                           palabraType.palabra, nCollisions, size);
                    break;
                }
            }

        }
    }

    return inserted;
}

PalabraType *search(PalabraTypeTableHash *tableHash, char *palabraBuscar, int tableSize, int *counterFounds){

    int nFounds = 0;
    PalabraType *response;

    printf("\nBuscando: %s \t", palabraBuscar);

    // Calcula key (k)
    int k = getAsciiValueFromString(palabraBuscar);

    // Obtiene h0
    int h0 = H(k, tableSize);

    // Si la primera validación no hay nada en h0 no existirá esa palabra en la tabla
    if(tableHash[h0].status == LIBRE){
        return FALSE;
    }

    if(strcmp(palabraBuscar, tableHash[h0].palabraType.palabra) == 0){
        nFounds++;
        response = (PalabraType *) malloc(sizeof(PalabraType) * nFounds);
        response[0] = tableHash[h0].palabraType;
    }

    int collisions = 1;
    int newH;
    while(collisions < tableSize){
        newH = G(k, collisions, tableSize);
        if(tableHash[newH].status == LIBRE){
            break;
        }
        if(strcmp(palabraBuscar, tableHash[newH].palabraType.palabra) == 0){
            nFounds++;
            PalabraType *tmp = realloc(response, sizeof(PalabraType) * nFounds);
            if (tmp) {
                response = tmp;
                response[nFounds-1] = tableHash[newH].palabraType;
            }else{
                perror("No se puede redimensionar respuesta");
                exit(EXIT_FAILURE);
            }
        }
        collisions++;
    }

    *counterFounds = nFounds;
    return response;
}


int G(int k, int i, int size) {
    int d = D(k, size);
    //printf("D=%d ", d);
    return ((H(k, size) + (d * i)) % size);
}

int D(int k, int size) {
    int d = k / size;
    if (d < 1) {
        return 1;
    }

    return d % 2 == 0 ? d + 1 : d;
}

int getInserted(PalabraTypeTableHash *tableHash, int size){
    int inserted = 0;
    for (int i = 0; i < size; i++) {
        if (tableHash[i].status == OCUPADO) {
            inserted += 1;
        }
    }
    return inserted;
}

float loadFactor(PalabraTypeTableHash *tableHash, int size) {
    float factor = ((float) getInserted(tableHash, size) / size);
    if((factor*100) > CLOUDY_LOAD_FACTOR){
        printf("Factor de carga: %.2f --> ", factor);
        printf("%.0f%% ocupado. Redimensionando!\n", factor * 100);
    }
    return factor;
}

int isLoadFactorCloudy(PalabraTypeTableHash *tableHash, int size) {
    return loadFactor(tableHash, size) * 100 > CLOUDY_LOAD_FACTOR ? TRUE : FALSE;
}

int isAvailable(int status) {
    int response = FALSE;

    if (LIBRE == status || BORRADO == status) {
        response = TRUE;
    }

    return response;
}
//
// Created by erik on 12/06/22.
//

#ifndef HASHING_HASH_H
#define HASHING_HASH_H

#include "types.h"

PalabraTypeTableHash *init(PalabraTypeTableHash *tableHash, int *size);

PalabraTypeTableHash *resizeTable(PalabraTypeTableHash *tableHash, int *currentSize);

/**
 * Inserta palabraType en tableHash y devuelve TRUE\n
 * Si no puede insertar devuelve FALSE
 * @param tableHash
 * @param palabraType
 * @param tableSize
 */
int insert(PalabraTypeTableHash *tableHash, PalabraType palabraType, int tableSize, int reinsert);

/**
 * Si palabra encontrada, se llena palabraTypeFound con cada palabra encontrada
 * @param tableHash
 * @param palabraBuscar
 * @param tableSize
 * @param palabraTypeFound
 * @return TRUE or FALSE
 */
PalabraType *search(PalabraTypeTableHash *tableHash, char *palabraBuscar, int tableSize, int *counterFounds);

int H(int k, int size);

int G(int k, int i, int size);

int D(int k, int size);

int getAsciiValueFromString(char *str);

int isAvailable(int status);

float loadFactor(PalabraTypeTableHash *tableHash, int size);

int getInserted(PalabraTypeTableHash *tableHash, int size);

/**
 * Mira si el factor de carga es mayor que el valor definico en CLOUDY_LOAD_FACTOR
 * @param tableHash
 * @param size
 * @return
 */
int isLoadFactorCloudy(PalabraTypeTableHash *tableHash, int size);

#endif //HASHING_HASH_H

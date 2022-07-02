//
// Created by erik on 12/06/22.
//

#ifndef HASHING_TYPES_H
#define HASHING_TYPES_H

#define CLOUDY_LOAD_FACTOR 80
#define OCUPADO 0
#define LIBRE -1
#define BORRADO -2

typedef struct palabraType {
    char *palabra;
    char *filename;
    int originalkey;
    int finalkey;
    int attempts;
} PalabraType;

typedef struct palabraHashReg {
    int status;
    PalabraType palabraType;
} PalabraTypeTableHash;

typedef struct responseSearch {
    char *filename;
    int repeated;
} ResponseSearch;

typedef enum {
    FALSE=0, TRUE=1
} Boolean;

typedef enum {
    SEARCH=1, RETURN=2, EXIT=0
} Option;

PalabraType *createPalabraType(char *filename, char *palabra);
int countRepeteadWord(PalabraType *list, char *filename, int size);

// Menu
int isValidOption(int option, int min, int max);

void printTableHash(PalabraTypeTableHash *tableHash, int size);
void printArrayPalabraType(PalabraType *list, int size);
void printArrayPalabraType(PalabraType *list, int size);
void printPalabraType(PalabraType type);

#endif //HASHING_TYPES_H

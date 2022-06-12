//
// Created by erik on 12/06/22.
//

#ifndef HASHING_HASH_H
#define HASHING_HASH_H

#define OCUPADO 0
#define LIBRE -1
#define BORRADO -2
#define NOT_FOUND -3
#define NOT_INSERTED -4

typedef struct palabraType
{
    char *palabra;
    char *filename;
    int originalkey;
    int finalkey;
    int attempts;
} PalabraType;

typedef struct palabraHashReg
{
    int status;
    PalabraType palabraType;
} PalabraHashReg;

int H(char *palabra, int size);
int get_key(char *palabra);

#endif //HASHING_HASH_H

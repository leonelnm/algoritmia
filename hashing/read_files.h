//
// Created by erik on 12/06/22.
//

#ifndef HASHING_READ_FILES_H
#define HASHING_READ_FILES_H

#include <stdio.h>
#include "hash.h"

int countWordsInFIle(FILE *file, int *longestWord);

PalabraType *getDataFromFile(char *filename, int *listSize);

char **getFilenamesList(int *listSize);

#endif //HASHING_READ_FILES_H

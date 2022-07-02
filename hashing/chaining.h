//
// Created by erik on 2/07/22.
//

#ifndef HASHING_CHAINING_H
#define HASHING_CHAINING_H

#include "types.h"
#include "dynamic_list.h"

int executeChaining(char **filename_list, int filenamelistSize);

P_NODO_LISTA *loadDataOnList(char **filename_list, int filenamelistSize, int size);

int countRepetedWordsOnList(P_NODO_LISTA list, char *filename, char *word);

void showResponse(P_NODO_LISTA list, char *word, char **filename_list, int filenamelistSize);

#endif //HASHING_CHAINING_H

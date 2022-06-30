//
// Created by erik on 25/06/22.
//

#ifndef ORDENACION_QUICKSORT_H
#define ORDENACION_QUICKSORT_H

#include "types.h"

void executeQuickSort(FileType **fileTypes, int orderBy);

void orderByQuickSort(FileType *fileType, int ini, int end, int orderBy, Boolean isRecursive);

void swap(char **a, char **b);

#endif //ORDENACION_QUICKSORT_H

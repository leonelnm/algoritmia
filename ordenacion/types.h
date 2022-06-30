//
// Created by erik on 18/06/22.
//

#ifndef ORDENACION_TYPES_H
#define ORDENACION_TYPES_H
#define MAX_LENGTH 10
#define N_FILES 3

typedef enum {
    ASC=1, DESC=2
} OrderBy;

typedef enum {
    BURBUJA=1, QUICKSORT=2
} Algorithm;

typedef enum {
    ALGORITHM, ORDERBY, EXIT=0
} Option;

typedef enum {
    FALSE, TRUE
} Boolean;

typedef struct fileType {
    char *filename;
    char *filenameOrdered;
    int nWords;
    char **words;
} FileType;

FileType *createFileType(char *filename, int nWords);
void freeFileType(FileType *ft);
char *getOrderType(int orderBy);

#endif //ORDENACION_TYPES_H

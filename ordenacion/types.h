//
// Created by erik on 18/06/22.
//

#ifndef ORDENACION_TYPES_H
#define ORDENACION_TYPES_H

typedef enum {
    FALSE, TRUE
} Boolean;

typedef struct fileType {
    char *filename;
    int nWords;
    char **words;
} FileType;

FileType *createFileType(char *filename, int nWords);
void freeFileType(FileType *ft);


#endif //ORDENACION_TYPES_H

#include <stdio.h>
#include "read_files.h"

int main() {
    int filenamelistSize = 0;

    printf("Buscando archivos en docs/ ...\n");
    char **filename_list = getFilenamesList(&filenamelistSize);

    int finalSize = 0;
    for (int i = 0; i < filenamelistSize; ++i) {
        int dataListSize = 0;
        PalabraType *data = getDataFromFile(filename_list[i], &dataListSize);

        for (int j = 0; j < dataListSize; ++j) {
            if(data[j].filename != NULL && data[j].palabra != NULL ){
                printf("Filename: %s\t%s\n", data[j].filename,  data[j].palabra);
            }
        }
        finalSize += dataListSize;
    }

    printf("\nFinal size %d\n", finalSize);

    return 0;
}

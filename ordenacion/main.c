#include <stdio.h>
#include <stdlib.h>
#include "fileUtils.h"
#include "types.h"

int main() {

    char filename[] = "words10.txt";

    FileType *f10 = createFileType(filename, 10);
    f10->words = readFile(f10->filename);
    //char **words = readFile(f10->filename);

    for (int i = 0; i <f10->nWords; ++i) {
        printf("%s\n", f10->words[i]);
    }

    freeFileType(f10);
    return 0;
}

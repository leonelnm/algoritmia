#include <stdio.h>
#include "read_files.h"
#include "rabin_karp.h"

int main() {
    char filename[] = "textobusq.txt";
    char pattern[] = "porompomrom";
    int q = 101; // primo seleccionado
    int size = countChars(filename);
    char *txt = getDataFromFile(filename, size);

    search(pattern, txt, q);

    return 0;
}

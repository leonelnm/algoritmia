//
// Created by erik on 12/06/22.
//

#include "hash.h"
#include <string.h>

int H(int k, int size) {
    return (k % size);
}

int getAsciiValueFromString(char *str) {
    int value = 0;
    for (int i = 0; i < strlen(str); i++) {
        value += str[i];
    }

    return value;
}




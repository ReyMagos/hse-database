#ifndef HSE_DATABASE_UTILS_H
#define HSE_DATABASE_UTILS_H

#include <ctype.h>

void input(const char* msg, char* dest, int count) {
    printf(msg);

    char *tmp = (char[count]) {};
    if (fgets(tmp, count, stdin) == NULL) {
        fprintf(stderr, "\nEOF when reading stdin\n");
        exit(EXIT_FAILURE);
    }

    // trim leading spaces
    while (isspace((unsigned char)*tmp)) tmp++;

    // trim trailing spaces
    char* end = tmp + strlen(tmp) - 1;
    while (end > tmp && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    int i = 0;
    while (tmp[i] != '\0') {
        dest[i] = tmp[i];
        ++i;
    }
    dest[i] = '\0';
}

#endif // HSE_DATABASE_UTILS_H

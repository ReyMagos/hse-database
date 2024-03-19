#include "utils.h"


void input(const char* msg, char* dest, int count) {
    printf(msg);

    char tmp[count];
    if (fgets(tmp, count, stdin) == NULL) {
        fprintf(stderr, "\nEOF when reading stdin\n");
        exit(EXIT_FAILURE);
    }

    // trim leading spaces
    int start = 0;
    while (isspace((unsigned char)tmp[start])) start++;

    // trim trailing spaces
    int end = start + strlen(tmp) - 1;
    while (end > start && isspace((unsigned char)tmp[end])) end--;
    tmp[end + 1] = '\0';

    int i = start;
    while (tmp[i] != '\0') {
        dest[i] = tmp[i];
        ++i;
    }
    dest[i] = '\0';
}

unsigned int_input(const char* msg) {
    char tmp[12];
    input(msg, tmp, 12);
    return strtoul(tmp, NULL, 10);
}

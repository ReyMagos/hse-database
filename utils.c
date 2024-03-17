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

uint32_t int_input(const char* msg) {
    char tmp[12];
    input(msg, tmp, 12);
    return strtoul(tmp, NULL, 10);
}

void success(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char msg[256];
    vsnprintf(msg, 256, fmt, args);
    printf("\x1b[32m⠿\x1b[0m %s\n", msg);

    va_end(args);

}

void wrong(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char msg[256];
    vsnprintf(msg, 256, fmt, args);
    printf("\x1b[31m⠿\x1b[0m %s\n", msg);

    va_end(args);
}

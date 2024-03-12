#include "database.h"

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10


void new_database(DatabaseContext *ctx) {
    ctx->length = 0;

    ctx->entries = malloc(sizeof(PassengerInfo) * INITIAL_CAPACITY);
    if (!ctx->entries) {
        fprintf(stderr, "malloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void destroy_database(DatabaseContext* ctx) {
    free(ctx->entries);
}

int read_database(DatabaseContext* ctx, FILE* db_file) {
    if (fread(&ctx->length, sizeof(uint32_t), 1, db_file))
        return 0;

    ctx->entries = malloc(sizeof(PassengerInfo) * ctx->length);
    if (!ctx->entries) {
        fprintf(stderr, "malloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (fread(ctx->entries, sizeof(PassengerInfo), ctx->length, db_file) < ctx->length)
        return 0;

    return 1;
}

int write_database(DatabaseContext* ctx, FILE* db_file) {
    fwrite(&ctx->length, sizeof(uint32_t), 1, db_file);
    fwrite(ctx->entries, sizeof(PassengerInfo), ctx->length, db_file);

    return 1;
}

void field_by_name(PassengerInfo *p, const char* name) {
    if (strcmp(name, "name") == 0) {

    } else if (strcmp(name, "cabin"))
}

void field_by_number(PassengerInfo *p, int n) {
    switch (n) {
        case 1:
            return p->name;
    }
}

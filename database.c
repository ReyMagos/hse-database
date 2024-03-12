#include "database.h"



void new_database(DatabaseContext *ctx) {
    ctx->length = 0;

    ctx->entries = malloc(sizeof(PassengerInfo));
    if (!ctx->entries) {
        fprintf(stderr, "malloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void destroy_database(DatabaseContext* ctx) {
    free(ctx->entries);
}

int read_database(DatabaseContext* ctx, FILE* db_file) {
    if (fread(&ctx->length, sizeof(uint32_t), 1, db_file) < 1)
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

char* field_by_name(PassengerInfo *info, const char* name) {
    char tmp[12];
    if (strcmp(name, "name") == 0) {
        return info->name;
    } else if (strcmp(name, "cabin") == 0) {
        snprintf(tmp, 12, "%u", info->cabin);
    } else if (strcmp(name, "cabin_type") == 0) {
        snprintf(tmp, 12, "%u", info->cabin_type);
    } else if (strcmp(name, "departure") == 0) {
        snprintf(tmp, 12, "%u", info->departure_port);
    } else if (strcmp(name, "arrival") == 0) {
        snprintf(tmp, 12, "%u", info->arrival_port);
    }

    return tmp;
}

char* field_by_number(PassengerInfo *info, int n) {
    const char* mapping[] = {"name", "cabin", "cabin_type", "departure", "arrival"};
    return field_by_name(info, mapping[n]);
}

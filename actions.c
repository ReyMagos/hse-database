#include "actions.h"

#include <stdio.h>
#include <wchar.h>

#include "utils.h"
#include "database.h"


void action_add(DatabaseContext* ctx) {
    printf("Creating a new entry");

    PassengerInfo info;
    input("Full name: ", info.name, 64);
    input("Cabin number: ", ..., 4);
    input("Cabin type", ..., 4);
    input("Departure port: ", ..., 8);
    input("Arrival port: ", ..., 8);

    printf("Entry %d successfully added", 0);
}

void action_del(DatabaseContext* ctx, uint32_t number) {
    char *answer[2];
    input("Are you sure to delete entry? [y/n]: ", answer, 2);

    if (strcmp(answer, "y") != 0)
        return;

    for (uint32_t i = number + 1; i < ctx->length; ++i) {
        ctx->entries[i - 1] = ctx->entries[i];
    }

    printf("Entry deleted\n");
}

void action_edit(DatabaseContext* ctx, uint32_t number) {

}

void print_table(PassengerInfo* entries, uint32_t count) {
    // id, name, cabin, cabin_type, departure, arrival
    const int sizes[] = {4, 32, 12, 12, 12, 12};
    const wchar_t *CORNER_LEFT_TOP = L"┌",
                   *CORNER_LEFT_BOTTOM = L"└",
                   *CORNER_RIGHT_TOP = L"┐",
                   *CORNER_RIGHT_BOTTOM = L"┘",
                   *HORIZONTAL = L"─",
                   *VERTICAL = L"│",
                   *T_TOP = L"┬",
                   *T_BOTTOM = L"┴";

    wprintf(CORNER_LEFT_TOP);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < sizes[i]; ++j)
            wprintf(HORIZONTAL);
        if (i < 5)
            wprintf(T_TOP);
    }
    wprintf(CORNER_RIGHT_TOP);

    wprintf(VERTICAL);
    for (uint32_t i = 0; i < count; ++i) {
        for (int j = 0; j < 6; ++j)
            printf("%*s\n", -sizes[i], field_by_number(entries[i], j));
        wprintf(VERTICAL);
    }

    wprintf(CORNER_LEFT_BOTTOM);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < sizes[i]; ++j)
            wprintf(HORIZONTAL);
        if (i < 5)
            wprintf(T_BOTTOM);
    }
    wprintf(CORNER_RIGHT_BOTTOM);
}

void action_search(DatabaseContext* ctx, const char* field, const char* value) {
    PassengerInfo result[];
    for (uint32_t i = 0; i < ctx->length; ++i) {

    }

    print_table(result, ...);
}

void action_list(DatabaseContext* ctx) {
    print_table(ctx->entries, ctx->length);
}


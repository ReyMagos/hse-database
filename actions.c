#include "actions.h"

#include "utils.h"


void action_add(DatabaseContext* ctx) {
    printf("Creating a new entry\n");

    PassengerInfo info;
    input("Full name: ", info.name, 32);

    char cabin[10];
    input("Cabin number: ", cabin, 10);
    info.cabin = (uint8_t)strtoul(cabin, NULL, 10);

    char cabin_type[10];
    input("Cabin type: ", cabin_type, 10);
    info.cabin_type = (uint8_t)strtoul(cabin_type, NULL, 10);

    char departure[10];
    input("Departure port: ", departure, 10);
    info.departure_port = (uint32_t)strtoul(departure, NULL, 10);

    char arrival[10];
    input("Arrival port: ", arrival, 10);
    info.arrival_port = (uint32_t)strtoul(arrival, NULL, 10);

    ctx->entries = realloc(ctx->entries, (ctx->length + 1) * sizeof(PassengerInfo));
    if (!ctx->entries) {
        fprintf(stderr, "realloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    ctx->entries[ctx->length] = info;

    printf("Entry %d successfully added\n", ctx->length++);
}

void action_del(DatabaseContext* ctx) {
    char *answer[12];
    input("Number: ", answer, 12);
    uint32_t number = strtoul(answer, NULL, 10);

    if (number >= ctx->length) {
        printf("Number is out of range\n");
        return;
    }

    input("Are you sure to delete entry? [y/n]: ", answer, 12);

    if (strcmp(answer, "y") != 0)
        return;

    for (uint32_t i = number + 1; i < ctx->length; ++i) {
        ctx->entries[i - 1] = ctx->entries[i];
    }
    --ctx->length;

    printf("Entry deleted\n");
}

void action_edit(DatabaseContext* ctx, uint32_t number) {

}

void print_table(uint32_t* numbers, PassengerInfo* entries, uint32_t count) {
    // number, name, cabin, cabin_type, departure, arrival
    const int width[] = {4, 32, 12, 12, 12, 12};
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
        for (int j = 0; j < width[i]; ++j)
            wprintf(HORIZONTAL);
        if (i < 5)
            wprintf(T_TOP);
    }
    wprintf(CORNER_RIGHT_TOP);
    printf("\n");

    const char* fields[] = {"", "name", "cabin", "cabin_type", "departure", "arrival"};
    wprintf(VERTICAL);
    for (int i = 0; i < 6; ++i) {
        printf(" %*s", -(width[i] - 1), fields[i]);
        wprintf(VERTICAL);
    }
    printf("\n");

    for (uint32_t i = 0; i < count; ++i) {
        wprintf(VERTICAL);
        printf(" %*u", -(width[0] - 1), numbers[i]);
        wprintf(VERTICAL);
        for (int j = 0; j < 5; ++j) {
            printf(" %*s", -(width[j + 1] - 1), field_by_number(&entries[i], j));
            wprintf(VERTICAL);
        }
        printf("\n");
    }

    wprintf(CORNER_LEFT_BOTTOM);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < width[i]; ++j)
            wprintf(HORIZONTAL);
        if (i < 5)
            wprintf(T_BOTTOM);
    }
    wprintf(CORNER_RIGHT_BOTTOM);
    printf("\n");
}

void action_search(DatabaseContext* ctx) {
    char* field[12];
    input("Field: ", field, 12);

    char* value[32];
    input("Value: ", value, 32);

    PassengerInfo result[ctx->length];
    uint32_t numbers[ctx->length];
    uint32_t count = 0;
    for (uint32_t i = 0; i < ctx->length; ++i) {
        PassengerInfo info = ctx->entries[i];

        if (strcmp(field_by_name(&info, field), value) == 0) {
            result[count] = info;
            numbers[count] = i;
            ++count;
        }
    }

    print_table(numbers, result, count);
}

void action_list(DatabaseContext* ctx) {
    uint32_t numbers[ctx->length];
    for (uint32_t i = 0; i < ctx->length; ++i)
        numbers[i] = i;

    print_table(numbers, ctx->entries, ctx->length);
}

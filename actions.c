#include "actions.h"
#include "utils.h"


void action_add(DatabaseContext* ctx) {
    printf("Creating a new entry\n");

    PassengerInfo info;
    input("Full name: ", info.name, 32);
    info.cabin = int_input("Cabin number: ");
    info.cabin_type = int_input("Cabin type: ");
    info.departure_port = int_input("Departure port: ");
    info.arrival_port = int_input("Arrival port: ");

    ctx->entries = realloc(ctx->entries, (ctx->length + 1) * sizeof(PassengerInfo));
    if (!ctx->entries) {
        fprintf(stderr, "realloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    ctx->entries[ctx->length] = info;

    printf("Entry %d successfully added\n", ctx->length++);
}

void action_del(DatabaseContext* ctx) {
    unsigned number = int_input("Number: ");
    if (number >= ctx->length) {
        printf("Number is out of range\n");
        return;
    }

    char answer[3];
    input("Are you sure to delete entry? [y/n]: ", answer, 3);
    if (strcmp(answer, "y") != 0)
        return;

    for (unsigned i = number + 1; i < ctx->length; ++i) {
        ctx->entries[i - 1] = ctx->entries[i];
    }
    --ctx->length;

    printf("Entry deleted\n");
}

void action_edit(DatabaseContext* ctx) {
    unsigned number = int_input("Number: ");
    if (number >= ctx->length) {
        printf("Number is out of range\n");
        return;
    }

    PassengerInfo* info = &ctx->entries[number];
    input("Full name: ", info->name, 32);
    info->cabin = int_input("Cabin number: ");
    info->cabin_type = int_input("Cabin type: ");
    info->departure_port = int_input("Departure port: ");
    info->arrival_port = int_input("Arrival port: ");

    printf("Changes applied\n");
}

void print_table(unsigned* numbers, PassengerInfo* entries, unsigned count) {
    // number, name, cabin, cabin_type, departure, arrival
    const int width[] = {4, 32, 12, 12, 12, 12};
    const char *CORNER_LEFT_TOP = "+",
               *CORNER_LEFT_BOTTOM = "+",
               *CORNER_RIGHT_TOP = "+",
               *CORNER_RIGHT_BOTTOM = "+",
               *HORIZONTAL = "-",
               *VERTICAL = "|",
               *T_TOP = "+",
               *T_BOTTOM = "+";

    printf(CORNER_LEFT_TOP);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < width[i]; ++j)
            printf(HORIZONTAL);
        if (i < 5)
            printf(T_TOP);
    }
    printf(CORNER_RIGHT_TOP);
    printf("\n");

    const char* fields[] = {"", "name", "cabin", "cabin_type", "departure", "arrival"};
    printf(VERTICAL);
    for (int i = 0; i < 6; ++i) {
        printf(" %*s", -(width[i] - 1), fields[i]);
        printf(VERTICAL);
    }
    printf("\n");

    for (unsigned i = 0; i < count; ++i) {
        printf(VERTICAL);
        printf(" %*u", -(width[0] - 1), numbers[i]);
        printf(VERTICAL);
        for (int j = 0; j < 5; ++j) {
            char *tmp[32];
            field_by_number(&entries[i], j, tmp);

            printf(" %*s", -(width[j + 1] - 1), tmp);
            printf(VERTICAL);
        }
        printf("\n");
    }

    printf(CORNER_LEFT_BOTTOM);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < width[i]; ++j)
            printf(HORIZONTAL);
        if (i < 5)
            printf(T_BOTTOM);
    }
    printf(CORNER_RIGHT_BOTTOM);

    printf("\n");
}

void action_search(DatabaseContext* ctx) {
    char* field[12];
    input("Field: ", field, 12);

    const char* fields[] = {"name", "cabin", "cabin_type", "departure", "arrival"};
    char exists = 0;
    for (int i = 0; i < 5; ++i) {
        if (strcmp(field, fields[i]) == 0) {
            exists = 1;
            break;
        }
    }

    if (!exists) {
        printf("No such field exists\n");
        return;
    }

    char* value[32];
    input("Value: ", value, 32);

    PassengerInfo result[ctx->length];
    unsigned numbers[ctx->length];
    unsigned count = 0;
    for (unsigned i = 0; i < ctx->length; ++i) {
        PassengerInfo info = ctx->entries[i];

        char *tmp[32];
        field_by_name(&info, field, tmp);

        if (strcmp(tmp, value) == 0) {
            result[count] = info;
            numbers[count] = i;
            ++count;
        }
    }

    print_table(numbers, result, count);
}

void action_list(DatabaseContext* ctx) {
    unsigned numbers[ctx->length];
    for (unsigned i = 0; i < ctx->length; ++i)
        numbers[i] = i;

    print_table(numbers, ctx->entries, ctx->length);
}

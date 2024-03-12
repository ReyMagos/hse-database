#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "database.h"
#include "actions.h"
#include "utils.h"

#define PATH_MAX 256


void print_help() {
    printf("Available commands:\n"
           "  add      Add entry to database\n"
           "  del      Remove entry from database\n"
           "  edit     Edit existing entry\n"
           "  search   Search entries\n"
           "  list     Prints table of entries\n"
           "  exit     Save database and exit\n"
           "  help     Prints this message\n");
}

int main(void) {
#ifdef MANUAL_INPUT
    PassengerInfo passengers[2] = {
            { "Andrey", 24, Luxury, 123, 321 },
            { "Elizaveta", 24, Luxury, 123, 321 }
    };

    DatabaseContext ctx = {
            .path = "/path/to/database.bin",
            .length = 2,
            .entries = passengers
    };

    FILE *db_file = fopen(ctx.path, "wb");
    write_database(&ctx, db_file);
    fclose(db_file);
#else
    // Disable stdout buffering to print without newline
    setbuf(stdout, NULL);

    // Set locale to utf-8 to print unicode chars
    setlocale(LC_ALL, "UTF-8");

    DatabaseContext ctx = { .path = (char[PATH_MAX]) {} };

    while (1) {
        // Database opening dialog
        input("Path to database or ENTER to create new: ", ctx.path, PATH_MAX);

        if (ctx.path[0] == '\0') {
            new_database(&ctx);
            printf("Created new database!\n");
        } else {
            FILE* db_file = fopen(ctx.path, "rb");

            if (db_file == NULL) {
                fprintf(stderr, "Error opening file \"%s\": %s\n", ctx.path, strerror(errno));
                continue;
            }

            if (!read_database(&ctx, db_file)) {
                fprintf(stderr, "Error reading file \"%s\" (perhaps wrong or corrupted file): %s\n",
                        ctx.path, strerror(errno));
                continue;
            }

            fclose(db_file);
            success("Database loaded");
        }

        // Main menu dialog
        print_help();

        while (1) {
            char command[256];
            input("> ", command, 256);

            if (strcmp(command, "add") == 0) {
                action_add(&ctx);
            } else if (strcmp(command, "del") == 0) {
                action_del(&ctx);
            } else if (strcmp(command, "edit") == 0) {
                action_edit(&ctx);
            } else if (strcmp(command, "search") == 0) {
                action_search(&ctx);
            } else if (strcmp(command, "list") == 0) {
                action_list(&ctx);
            } else if (strcmp(command, "exit") == 0) {
                break;
            } else if (strcmp(command, "help") == 0) {
                print_help();
            } else {
                wrong("Unknown command");
            }
        }

        // Database saving dialog
        while (1) {
            char answer[PATH_MAX];
            char* save_path = answer;
            if (ctx.path[0] == '\0') {
                input("Where to save database: ", answer, PATH_MAX);
            } else {
                char msg[28 + PATH_MAX];
                snprintf(msg, 28 + PATH_MAX, "Where to save database [%s]: ", ctx.path);
                input(msg, answer, PATH_MAX);

                if (save_path[0] == '\0')
                    save_path = ctx.path;
            }

            FILE *db_file = fopen(save_path, "wb");

            if (db_file == NULL) {
                fprintf(stderr, "Error opening file \"%s\": %s\n", save_path, strerror(errno));
                continue;
            }

            if (!write_database(&ctx, db_file)) {
                fprintf(stderr, "Error writing file \"%s\": %s\n", save_path, strerror(errno));
                continue;
            }

            fclose(db_file);
            destroy_database(&ctx);
            success("Database saved");
            break;
        }
    }
#endif

    return 0;
}

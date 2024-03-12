#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "database.h"
#include "actions.h"
#include "utils.h"

#define PATH_MAX 256


int main(void) {
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
            printf("Database loaded!\n");
        }

        printf("Available commands:\n"
               "  add                      Add entry to database\n"
               "  del <number>             Remove entry from database\n"
               "  edit <number>            Edit existing entry\n"
               "  search <field> <value>   Search entries\n"
               "  list                     Print table of entries\n"
               "  exit                     Save database and exit\n");

        // Main menu dialog
        while (1) {
            char command[256];
            input("> ", command, 256);

            if (strcmp(command, "add") == 0) {
                action_add(&ctx);
            } else if (strcmp(command, "del") == 0) {
                action_del(&ctx, 0);
            } else if (strcmp(command, "edit") == 0) {
                action_edit(&ctx, 0);
            } else if (strcmp(command, "search") == 0) {
                action_search(&ctx);
            } else if (strcmp(command, "list") == 0) {
                action_list(&ctx);
            } else if (strcmp(command, "exit") == 0) {
                break;
            } else {
                fprintf(stderr, "Unknown command\n");
            }
        }

        // Database saving dialog
        while (1) {
            char *save_path[PATH_MAX];
            if (ctx.path[0] == '\0') {
                input("Where to save database: ", save_path, PATH_MAX);
            } else {
                char msg[28 + PATH_MAX];
                snprintf(msg, 28 + PATH_MAX, "Where to save database [%s]: ", ctx.path);
                input(msg, save_path, PATH_MAX);
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
            printf("Database saved!\n");
            break;
        }
    }

    return 0;
}

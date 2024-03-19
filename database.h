#ifndef HSE_DATABASE_DATABASE_H
#define HSE_DATABASE_DATABASE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    Luxury = 0,
    FirstClass = 1,
    SecondClass = 2,
    ThirdClass = 3
} CabinType;

typedef struct {
    char name[32];
    unsigned cabin;
    CabinType cabin_type;
    unsigned departure_port;
    unsigned arrival_port;
} PassengerInfo;

void field_by_name(PassengerInfo *info, const char* name, char* dest);
void field_by_number(PassengerInfo *p, int n, char* dest);

typedef struct {
    char* path;
    unsigned length;
    PassengerInfo* entries;
} DatabaseContext;

void new_database(DatabaseContext* ctx);
void destroy_database(DatabaseContext* ctx);
int read_database(DatabaseContext* ctx, FILE* db_file);
int write_database(DatabaseContext* ctx, FILE* db_file);

#endif // HSE_DATABASE_DATABASE_H

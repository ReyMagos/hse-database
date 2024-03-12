#ifndef HSE_DATABASE_DATABASE_H
#define HSE_DATABASE_DATABASE_H

#include <stdint.h>
#include <stdio.h>

typedef enum {
    Luxury = 0,
    FirstClass = 1,
    SecondClass = 2,
    ThirdClass = 3
} CabinType;

typedef struct {
    char name[64];
    uint8_t cabin;
    CabinType cabin_type;
    uint32_t departure_port;
    uint32_t arrival_port;
} PassengerInfo;

typedef struct {
    char* path;
    uint32_t length;
    PassengerInfo* entries;
} DatabaseContext;

void new_database(DatabaseContext*);
void destroy_database(DatabaseContext*);
int read_database(DatabaseContext*, FILE*);
int write_database(DatabaseContext*, FILE*);

#endif // HSE_DATABASE_DATABASE_H

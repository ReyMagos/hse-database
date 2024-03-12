#ifndef HSE_DATABASE_ACTIONS_H
#define HSE_DATABASE_ACTIONS_H

#include "database.h"

void action_add(DatabaseContext*);
void action_del(DatabaseContext*, uint32_t);
void action_edit(DatabaseContext*, uint32_t);
void action_search(DatabaseContext*, const char*, const char*);
void action_list(DatabaseContext*);

#endif // HSE_DATABASE_ACTIONS_H

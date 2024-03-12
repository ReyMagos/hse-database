#ifndef HSE_DATABASE_ACTIONS_H
#define HSE_DATABASE_ACTIONS_H

#include <stdio.h>
#include <wchar.h>
#include <errno.h>

#include "database.h"

void action_add(DatabaseContext* ctx);
void action_del(DatabaseContext* ctx);
void action_edit(DatabaseContext* ctx);
void action_search(DatabaseContext* ctx);
void action_list(DatabaseContext* ctx);

#endif // HSE_DATABASE_ACTIONS_H

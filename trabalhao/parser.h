#ifndef PARSER_H
#define PARSER_H

#include "database.h"

void printHelp(void);
void executeCommand(Database *db, char *command, int *running);

#endif

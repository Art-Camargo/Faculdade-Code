#include "database.h"
#include "parser.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 2048
#define LINE_SIZE 512

static int commandNeedsMoreLines(const char *command);

int main(void)
{
    Database db;
    char command[INPUT_SIZE];
    char line[LINE_SIZE];
    int running;

    initDatabase(&db);
    loadDatabase(&db);

    printf("=================================\n");
    printf("        CSQL - Cria SQL\n");
    printf("=================================\n\n");
    printf("Digite HELP para ajuda.\n\n");

    running = 1;
    while (running)
    {
        printf("csql>");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }

        remove_newline(command);

        /*
         * Parser simples com fgets: para CREATE/INSERT/UPDATE escritos em
         * varias linhas, juntamos as linhas antes de interpretar o comando.
         */
        while (commandNeedsMoreLines(command))
        {
            printf("...>");
            if (fgets(line, sizeof(line), stdin) == NULL)
            {
                break;
            }

            if (strlen(command) + strlen(line) + 2 >= sizeof(command))
            {
                printf("Erro: comando muito grande.\n");
                command[0] = '\0';
                break;
            }

            strcat(command, " ");
            strcat(command, line);
            remove_newline(command);
        }

        executeCommand(&db, command, &running);
    }

    freeDatabase(&db);
    return 0;
}

static int commandNeedsMoreLines(const char *command)
{
    char upper[INPUT_SIZE];

    strncpy(upper, command, sizeof(upper) - 1);
    upper[sizeof(upper) - 1] = '\0';
    to_upper_string(upper);

    if (starts_with_ignore_case(upper, "CREATE TABLE") && strchr(upper, ')') == NULL)
    {
        return 1;
    }

    if (starts_with_ignore_case(upper, "INSERT INTO") && strchr(upper, ')') == NULL)
    {
        return 1;
    }

    if (starts_with_ignore_case(upper, "UPDATE") &&
        (strstr(upper, " SET ") == NULL || strstr(upper, " WHERE ") == NULL))
    {
        return 1;
    }

    return 0;
}

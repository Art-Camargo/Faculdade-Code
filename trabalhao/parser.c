#include "parser.h"

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 80

static void parseCreate(Database *db, char *command);
static void parseInsert(Database *db, char *command);
static void parseSelect(Database *db, char *command);
static void parseDelete(Database *db, char *command);
static void parseUpdate(Database *db, char *command);
static int parseCommaList(char *text, char ***items, int *count);
static void freeStringArray(char **items, int count);
static int tokenizeCommand(char *command, char tokens[MAX_TOKENS][MAX_NAME]);
static int splitQualifiedName(const char *qualified, char *tableName, char *columnName);

void printHelp(void)
{
    printf("\n");
    printf("Comandos disponiveis:\n");
    printf("  HELP\n");
    printf("  SHOW TABLES\n");
    printf("  CREATE TABLE usuarios ( id, nome, idade )\n");
    printf("  INSERT INTO usuarios VALUES ( 1, Allan, 25 )\n");
    printf("  SELECT * FROM usuarios\n");
    printf("  SELECT nome FROM usuarios\n");
    printf("  UPDATE usuarios SET idade = 30 WHERE id = 1\n");
    printf("  DELETE FROM usuarios WHERE id = 2\n");
    printf("  SELECT * FROM usuarios JOIN pedidos ON usuarios.id = pedidos.user_id\n");
    printf("  DEMO\n");
    printf("  SAVE\n");
    printf("  EXIT\n");
    printf("\n");
}

void executeCommand(Database *db, char *command, int *running)
{
    char cleanCommand[2048];

    if (command == NULL)
    {
        return;
    }

    strncpy(cleanCommand, command, sizeof(cleanCommand) - 1);
    cleanCommand[sizeof(cleanCommand) - 1] = '\0';
    trim(cleanCommand);

    if (cleanCommand[0] == '\0')
    {
        return;
    }

    if (equals_ignore_case(cleanCommand, "HELP"))
    {
        printHelp();
    }
    else if (equals_ignore_case(cleanCommand, "SHOW TABLES"))
    {
        showTables(db);
    }
    else if (equals_ignore_case(cleanCommand, "SAVE"))
    {
        saveDatabase(db);
    }
    else if (equals_ignore_case(cleanCommand, "DEMO"))
    {
        createDemo(db);
    }
    else if (equals_ignore_case(cleanCommand, "EXIT") || equals_ignore_case(cleanCommand, "QUIT"))
    {
        saveDatabase(db);
        *running = 0;
    }
    else if (starts_with_ignore_case(cleanCommand, "CREATE TABLE"))
    {
        parseCreate(db, cleanCommand);
    }
    else if (starts_with_ignore_case(cleanCommand, "INSERT INTO"))
    {
        parseInsert(db, cleanCommand);
    }
    else if (starts_with_ignore_case(cleanCommand, "SELECT"))
    {
        parseSelect(db, cleanCommand);
    }
    else if (starts_with_ignore_case(cleanCommand, "DELETE FROM"))
    {
        parseDelete(db, cleanCommand);
    }
    else if (starts_with_ignore_case(cleanCommand, "UPDATE"))
    {
        parseUpdate(db, cleanCommand);
    }
    else
    {
        printf("Comando nao reconhecido. Digite HELP para ajuda.\n");
    }
}

static void parseCreate(Database *db, char *command)
{
    char beforeParenthesis[256];
    char tableName[MAX_NAME];
    char *openParenthesis;
    char *closeParenthesis;
    char *inside;
    char **columns;
    int columnCount;

    openParenthesis = strchr(command, '(');
    closeParenthesis = strrchr(command, ')');

    if (openParenthesis == NULL || closeParenthesis == NULL || closeParenthesis <= openParenthesis)
    {
        printf("Erro: use CREATE TABLE nome ( coluna1, coluna2 ).\n");
        return;
    }

    strncpy(beforeParenthesis, command, openParenthesis - command);
    beforeParenthesis[openParenthesis - command] = '\0';

    tableName[0] = '\0';
    if (sscanf(beforeParenthesis, "%*s %*s %49s", tableName) != 1)
    {
        printf("Erro: nome da tabela nao informado.\n");
        return;
    }

    inside = csql_strdup(openParenthesis + 1);
    if (inside == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        return;
    }

    inside[closeParenthesis - openParenthesis - 1] = '\0';
    columns = NULL;
    columnCount = 0;

    if (parseCommaList(inside, &columns, &columnCount))
    {
        createTable(db, tableName, columns, columnCount);
        freeStringArray(columns, columnCount);
    }
    else
    {
        printf("Erro: colunas invalidas.\n");
    }

    free(inside);
}

static void parseInsert(Database *db, char *command)
{
    char tokens[MAX_TOKENS][MAX_NAME];
    char tableName[MAX_NAME];
    char *openParenthesis;
    char *closeParenthesis;
    char *inside;
    char **values;
    int valueCount;
    int tokenCount;

    tokenCount = tokenizeCommand(command, tokens);
    if (tokenCount < 4 || !equals_ignore_case(tokens[0], "INSERT") ||
        !equals_ignore_case(tokens[1], "INTO") || !equals_ignore_case(tokens[3], "VALUES"))
    {
        printf("Erro: use INSERT INTO tabela VALUES ( valor1, valor2 ).\n");
        return;
    }

    strncpy(tableName, tokens[2], MAX_NAME - 1);
    tableName[MAX_NAME - 1] = '\0';

    openParenthesis = strchr(command, '(');
    closeParenthesis = strrchr(command, ')');

    if (openParenthesis == NULL || closeParenthesis == NULL || closeParenthesis <= openParenthesis)
    {
        printf("Erro: valores devem ficar entre parenteses.\n");
        return;
    }

    inside = csql_strdup(openParenthesis + 1);
    if (inside == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        return;
    }

    inside[closeParenthesis - openParenthesis - 1] = '\0';
    values = NULL;
    valueCount = 0;

    if (parseCommaList(inside, &values, &valueCount))
    {
        insertRow(db, tableName, values, valueCount);
        freeStringArray(values, valueCount);
    }
    else
    {
        printf("Erro: valores invalidos.\n");
    }

    free(inside);
}

static void parseSelect(Database *db, char *command)
{
    char tokens[MAX_TOKENS][MAX_NAME];
    char leftTable[MAX_NAME];
    char rightTable[MAX_NAME];
    char leftColumn[MAX_NAME];
    char rightColumn[MAX_NAME];
    int tokenCount;

    tokenCount = tokenizeCommand(command, tokens);

    if (tokenCount == 4 && equals_ignore_case(tokens[0], "SELECT") &&
        equals_ignore_case(tokens[2], "FROM"))
    {
        selectRows(db, tokens[3], tokens[1]);
        return;
    }

    if (tokenCount >= 9 && equals_ignore_case(tokens[0], "SELECT") &&
        strcmp(tokens[1], "*") == 0 && equals_ignore_case(tokens[2], "FROM") &&
        equals_ignore_case(tokens[4], "JOIN") && equals_ignore_case(tokens[6], "ON"))
    {
        if (!splitQualifiedName(tokens[7], leftTable, leftColumn) ||
            !splitQualifiedName(tokens[8], rightTable, rightColumn))
        {
            printf("Erro: use ON tabela1.coluna = tabela2.coluna.\n");
            return;
        }

        if (strcmp(tokens[3], leftTable) != 0 || strcmp(tokens[5], rightTable) != 0)
        {
            printf("Erro: as tabelas do ON devem seguir a ordem do FROM/JOIN.\n");
            return;
        }

        innerJoin(db, tokens[3], tokens[5], leftColumn, rightColumn);
        return;
    }

    printf("Erro: use SELECT * FROM tabela, SELECT coluna FROM tabela ou SELECT * FROM t1 JOIN t2 ON t1.c = t2.c.\n");
}

static void parseDelete(Database *db, char *command)
{
    char tokens[MAX_TOKENS][MAX_NAME];
    int tokenCount;

    tokenCount = tokenizeCommand(command, tokens);

    if (tokenCount < 6 || !equals_ignore_case(tokens[0], "DELETE") ||
        !equals_ignore_case(tokens[1], "FROM") || !equals_ignore_case(tokens[3], "WHERE"))
    {
        printf("Erro: use DELETE FROM tabela WHERE coluna = valor.\n");
        return;
    }

    deleteRows(db, tokens[2], tokens[4], tokens[5]);
}

static void parseUpdate(Database *db, char *command)
{
    char tokens[MAX_TOKENS][MAX_NAME];
    int tokenCount;

    tokenCount = tokenizeCommand(command, tokens);

    if (tokenCount < 8 || !equals_ignore_case(tokens[0], "UPDATE") ||
        !equals_ignore_case(tokens[2], "SET") || !equals_ignore_case(tokens[5], "WHERE"))
    {
        printf("Erro: use UPDATE tabela SET coluna = valor WHERE coluna = valor.\n");
        return;
    }

    updateRows(db, tokens[1], tokens[3], tokens[4], tokens[6], tokens[7]);
}

static int parseCommaList(char *text, char ***items, int *count)
{
    char **list;
    char **newList;
    char *token;
    char *copy;
    int total;

    list = NULL;
    total = 0;

    token = strtok(text, ",");
    while (token != NULL)
    {
        trim(token);

        if (token[0] == '\0')
        {
            freeStringArray(list, total);
            return 0;
        }

        newList = (char **)realloc(list, sizeof(char *) * (total + 1));
        if (newList == NULL)
        {
            freeStringArray(list, total);
            return 0;
        }

        list = newList;
        copy = csql_strdup(token);
        if (copy == NULL)
        {
            freeStringArray(list, total);
            return 0;
        }

        list[total] = copy;
        total++;
        token = strtok(NULL, ",");
    }

    if (total == 0)
    {
        return 0;
    }

    *items = list;
    *count = total;
    return 1;
}

static void freeStringArray(char **items, int count)
{
    int i;

    if (items == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(items[i]);
    }

    free(items);
}

static int tokenizeCommand(char *command, char tokens[MAX_TOKENS][MAX_NAME])
{
    char buffer[2048];
    char *token;
    int count;
    int i;

    strncpy(buffer, command, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '=' || buffer[i] == '(' || buffer[i] == ')' || buffer[i] == ',' ||
            buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == ';')
        {
            buffer[i] = ' ';
        }
    }

    count = 0;
    token = strtok(buffer, " \t");
    while (token != NULL && count < MAX_TOKENS)
    {
        strncpy(tokens[count], token, MAX_NAME - 1);
        tokens[count][MAX_NAME - 1] = '\0';
        count++;
        token = strtok(NULL, " \t");
    }

    return count;
}

static int splitQualifiedName(const char *qualified, char *tableName, char *columnName)
{
    char buffer[MAX_NAME * 2];
    char *dot;

    strncpy(buffer, qualified, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    dot = strchr(buffer, '.');
    if (dot == NULL)
    {
        return 0;
    }

    *dot = '\0';
    strncpy(tableName, buffer, MAX_NAME - 1);
    tableName[MAX_NAME - 1] = '\0';
    strncpy(columnName, dot + 1, MAX_NAME - 1);
    columnName[MAX_NAME - 1] = '\0';

    return tableName[0] != '\0' && columnName[0] != '\0';
}

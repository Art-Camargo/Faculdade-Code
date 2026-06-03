#include "database.h"

#include "utils.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static int findColumnIndex(Table *table, const char *columnName);
static void freeTable(Table *table);
static void freeRow(Row *row, int columnCount);
static int appendRowToTable(Table *table, char **values);
static int addTableLoaded(Database *db, Table *loadedTable);
static int saveTable(Table *table);
static int loadTableFromFile(Database *db, const char *filePath);
static int parsePipeValues(char *line, char ***values, int expectedCount);
static void freeStringArray(char **values, int count);
static void clearDatabase(Database *db);
static void ensureDataDirectory(void);

/*
 * REQUISITO: passagem por referencia usando ponteiro.
 * A funcao altera o Database recebido, sem precisar retornar uma copia.
 */
void initDatabase(Database *db)
{
    db->tables = NULL;
    db->tableCount = 0;
}

void freeDatabase(Database *db)
{
    int i;

    if (db == NULL)
    {
        return;
    }

    for (i = 0; i < db->tableCount; i++)
    {
        freeTable(&db->tables[i]);
    }

    free(db->tables);
    db->tables = NULL;
    db->tableCount = 0;
}

Table *findTable(Database *db, const char *name)
{
    int i;

    if (db == NULL || name == NULL)
    {
        return NULL;
    }

    for (i = 0; i < db->tableCount; i++)
    {
        if (strcmp(db->tables[i].name, name) == 0)
        {
            return &db->tables[i];
        }
    }

    return NULL;
}

int createTable(Database *db, const char *tableName, char **columnNames, int columnCount)
{
    Table *newTables;
    Table *table;
    int i;

    if (db == NULL || tableName == NULL || columnNames == NULL || columnCount <= 0)
    {
        printf("Erro: dados invalidos para criar tabela.\n");
        return 0;
    }

    if (!is_valid_name(tableName))
    {
        printf("Erro: nome de tabela invalido. Use letras, numeros e underline.\n");
        return 0;
    }

    if (findTable(db, tableName) != NULL)
    {
        printf("Erro: tabela '%s' ja existe.\n", tableName);
        return 0;
    }

    newTables = (Table *)realloc(db->tables, sizeof(Table) * (db->tableCount + 1));
    if (newTables == NULL)
    {
        printf("Erro: memoria insuficiente para criar tabela.\n");
        return 0;
    }

    db->tables = newTables;
    table = &db->tables[db->tableCount];

    strncpy(table->name, tableName, MAX_NAME - 1);
    table->name[MAX_NAME - 1] = '\0';
    table->columnCount = columnCount;
    table->rowCount = 0;
    table->rows = NULL;

    table->columns = (Column *)malloc(sizeof(Column) * columnCount);
    if (table->columns == NULL)
    {
        printf("Erro: memoria insuficiente para criar colunas.\n");
        table->name[0] = '\0';
        table->columnCount = 0;
        return 0;
    }

    for (i = 0; i < columnCount; i++)
    {
        if (!is_valid_name(columnNames[i]))
        {
            printf("Erro: nome de coluna invalido: %s\n", columnNames[i]);
            free(table->columns);
            table->columns = NULL;
            table->columnCount = 0;
            return 0;
        }

        strncpy(table->columns[i].name, columnNames[i], MAX_NAME - 1);
        table->columns[i].name[MAX_NAME - 1] = '\0';
        strcpy(table->columns[i].type, "TEXT");
    }

    db->tableCount++;
    printf("Tabela '%s' criada com sucesso.\n", tableName);
    return 1;
}

int insertRow(Database *db, const char *tableName, char **values, int valueCount)
{
    Table *table;

    table = findTable(db, tableName);
    if (table == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", tableName);
        return 0;
    }

    if (valueCount != table->columnCount)
    {
        printf("Erro: quantidade de valores diferente da quantidade de colunas.\n");
        return 0;
    }

    if (!appendRowToTable(table, values))
    {
        printf("Erro: memoria insuficiente para inserir registro.\n");
        return 0;
    }

    printf("Registro inserido em '%s'.\n", tableName);
    return 1;
}

int selectRows(Database *db, const char *tableName, const char *columnName)
{
    Table *table;
    int columnIndex;
    int i;
    int j;

    table = findTable(db, tableName);
    if (table == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", tableName);
        return 0;
    }

    if (strcmp(columnName, "*") == 0)
    {
        for (i = 0; i < table->columnCount; i++)
        {
            printf("%s", table->columns[i].name);
            if (i < table->columnCount - 1)
            {
                printf("\t");
            }
        }
        printf("\n");

        for (i = 0; i < table->rowCount; i++)
        {
            for (j = 0; j < table->columnCount; j++)
            {
                printf("%s", table->rows[i].values[j]);
                if (j < table->columnCount - 1)
                {
                    printf("\t");
                }
            }
            printf("\n");
        }
        return 1;
    }

    columnIndex = findColumnIndex(table, columnName);
    if (columnIndex < 0)
    {
        printf("Erro: coluna '%s' nao encontrada.\n", columnName);
        return 0;
    }

    printf("%s\n", table->columns[columnIndex].name);
    for (i = 0; i < table->rowCount; i++)
    {
        printf("%s\n", table->rows[i].values[columnIndex]);
    }

    return 1;
}

int deleteRows(Database *db, const char *tableName, const char *whereColumn, const char *whereValue)
{
    Table *table;
    int columnIndex;
    int i;
    int deleted;

    table = findTable(db, tableName);
    if (table == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", tableName);
        return 0;
    }

    columnIndex = findColumnIndex(table, whereColumn);
    if (columnIndex < 0)
    {
        printf("Erro: coluna '%s' nao encontrada.\n", whereColumn);
        return 0;
    }

    deleted = 0;
    i = 0;
    while (i < table->rowCount)
    {
        if (strcmp(table->rows[i].values[columnIndex], whereValue) == 0)
        {
            freeRow(&table->rows[i], table->columnCount);

            if (i < table->rowCount - 1)
            {
                memmove(&table->rows[i], &table->rows[i + 1], sizeof(Row) * (table->rowCount - i - 1));
            }

            table->rowCount--;
            deleted++;
        }
        else
        {
            i++;
        }
    }

    if (table->rowCount == 0)
    {
        free(table->rows);
        table->rows = NULL;
    }
    else
    {
        Row *newRows = (Row *)realloc(table->rows, sizeof(Row) * table->rowCount);
        if (newRows != NULL)
        {
            table->rows = newRows;
        }
    }

    printf("%d registro(s) removido(s).\n", deleted);
    return 1;
}

int updateRows(Database *db, const char *tableName, const char *setColumn, const char *setValue,
               const char *whereColumn, const char *whereValue)
{
    Table *table;
    int setIndex;
    int whereIndex;
    int i;
    int updated;
    char *copy;

    table = findTable(db, tableName);
    if (table == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", tableName);
        return 0;
    }

    setIndex = findColumnIndex(table, setColumn);
    whereIndex = findColumnIndex(table, whereColumn);

    if (setIndex < 0)
    {
        printf("Erro: coluna '%s' nao encontrada.\n", setColumn);
        return 0;
    }

    if (whereIndex < 0)
    {
        printf("Erro: coluna '%s' nao encontrada.\n", whereColumn);
        return 0;
    }

    updated = 0;
    for (i = 0; i < table->rowCount; i++)
    {
        if (strcmp(table->rows[i].values[whereIndex], whereValue) == 0)
        {
            copy = csql_strdup(setValue);
            if (copy == NULL)
            {
                printf("Erro: memoria insuficiente para atualizar valor.\n");
                return 0;
            }
            free(table->rows[i].values[setIndex]);
            table->rows[i].values[setIndex] = copy;
            updated++;
        }
    }

    printf("%d registro(s) atualizado(s).\n", updated);
    return 1;
}

int innerJoin(Database *db, const char *leftTableName, const char *rightTableName,
              const char *leftColumnName, const char *rightColumnName)
{
    Table *leftTable;
    Table *rightTable;
    int leftIndex;
    int rightIndex;
    int i;
    int j;
    int k;
    int found;

    leftTable = findTable(db, leftTableName);
    rightTable = findTable(db, rightTableName);

    if (leftTable == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", leftTableName);
        return 0;
    }

    if (rightTable == NULL)
    {
        printf("Erro: tabela '%s' nao encontrada.\n", rightTableName);
        return 0;
    }

    leftIndex = findColumnIndex(leftTable, leftColumnName);
    rightIndex = findColumnIndex(rightTable, rightColumnName);

    if (leftIndex < 0)
    {
        printf("Erro: coluna '%s.%s' nao encontrada.\n", leftTableName, leftColumnName);
        return 0;
    }

    if (rightIndex < 0)
    {
        printf("Erro: coluna '%s.%s' nao encontrada.\n", rightTableName, rightColumnName);
        return 0;
    }

    /*
     * JOIN simplificado: dois lacos percorrem as tabelas e comparam
     * os valores das colunas escolhidas. Nao ha otimizacao de banco real.
     */
    for (i = 0; i < leftTable->columnCount; i++)
    {
        printf("%s.%s\t", leftTable->name, leftTable->columns[i].name);
    }
    for (i = 0; i < rightTable->columnCount; i++)
    {
        printf("%s.%s", rightTable->name, rightTable->columns[i].name);
        if (i < rightTable->columnCount - 1)
        {
            printf("\t");
        }
    }
    printf("\n");

    found = 0;
    for (i = 0; i < leftTable->rowCount; i++)
    {
        for (j = 0; j < rightTable->rowCount; j++)
        {
            if (strcmp(leftTable->rows[i].values[leftIndex], rightTable->rows[j].values[rightIndex]) == 0)
            {
                for (k = 0; k < leftTable->columnCount; k++)
                {
                    printf("%s\t", leftTable->rows[i].values[k]);
                }
                for (k = 0; k < rightTable->columnCount; k++)
                {
                    printf("%s", rightTable->rows[j].values[k]);
                    if (k < rightTable->columnCount - 1)
                    {
                        printf("\t");
                    }
                }
                printf("\n");
                found++;
            }
        }
    }

    if (found == 0)
    {
        printf("(nenhum registro encontrado)\n");
    }

    return 1;
}

void showTables(Database *db)
{
    int i;

    if (db == NULL || db->tableCount == 0)
    {
        printf("(nenhuma tabela)\n");
        return;
    }

    for (i = 0; i < db->tableCount; i++)
    {
        printf("%s\n", db->tables[i].name);
    }
}

void createDemo(Database *db)
{
    char *usuariosColumns[] = {"id", "nome"};
    char *pedidosColumns[] = {"id", "user_id", "produto"};
    char *usuario1[] = {"1", "Allan"};
    char *usuario2[] = {"2", "Tui"};
    char *pedido1[] = {"1", "1", "Coca"};
    char *pedido2[] = {"2", "2", "Xis"};

    if (findTable(db, "usuarios") == NULL)
    {
        createTable(db, "usuarios", usuariosColumns, 2);
        insertRow(db, "usuarios", usuario1, 2);
        insertRow(db, "usuarios", usuario2, 2);
    }
    else
    {
        printf("Tabela 'usuarios' ja existe. Mantendo dados atuais.\n");
    }

    if (findTable(db, "pedidos") == NULL)
    {
        createTable(db, "pedidos", pedidosColumns, 3);
        insertRow(db, "pedidos", pedido1, 3);
        insertRow(db, "pedidos", pedido2, 3);
    }
    else
    {
        printf("Tabela 'pedidos' ja existe. Mantendo dados atuais.\n");
    }

    printf("DEMO pronta. Teste: SELECT * FROM usuarios JOIN pedidos ON usuarios.id = pedidos.user_id\n");
}

int saveDatabase(Database *db)
{
    int i;
    int ok;

    if (db == NULL)
    {
        return 0;
    }

    ensureDataDirectory();

    ok = 1;
    for (i = 0; i < db->tableCount; i++)
    {
        if (!saveTable(&db->tables[i]))
        {
            ok = 0;
        }
    }

    if (ok)
    {
        printf("Banco salvo em disco.\n");
    }
    else
    {
        printf("Aviso: houve erro ao salvar alguma tabela.\n");
    }

    return ok;
}

int loadDatabase(Database *db)
{
    DIR *dir;
    struct dirent *entry;
    char filePath[512];
    int loaded;
    int nameLength;

    if (db == NULL)
    {
        return 0;
    }

    ensureDataDirectory();
    clearDatabase(db);

    dir = opendir(DATA_DIR);
    if (dir == NULL)
    {
        return 0;
    }

    loaded = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        nameLength = (int)strlen(entry->d_name);
        if (nameLength > 4 && strcmp(entry->d_name + nameLength - 4, ".tbl") == 0)
        {
            snprintf(filePath, sizeof(filePath), "%s/%s", DATA_DIR, entry->d_name);
            if (loadTableFromFile(db, filePath))
            {
                loaded++;
            }
        }
    }

    closedir(dir);

    if (loaded > 0)
    {
        printf("%d tabela(s) carregada(s) do disco.\n", loaded);
    }

    return 1;
}

static int findColumnIndex(Table *table, const char *columnName)
{
    int i;

    if (table == NULL || columnName == NULL)
    {
        return -1;
    }

    for (i = 0; i < table->columnCount; i++)
    {
        if (strcmp(table->columns[i].name, columnName) == 0)
        {
            return i;
        }
    }

    return -1;
}

static void freeTable(Table *table)
{
    int i;

    if (table == NULL)
    {
        return;
    }

    for (i = 0; i < table->rowCount; i++)
    {
        freeRow(&table->rows[i], table->columnCount);
    }

    free(table->rows);
    free(table->columns);

    table->rows = NULL;
    table->columns = NULL;
    table->rowCount = 0;
    table->columnCount = 0;
    table->name[0] = '\0';
}

static void freeRow(Row *row, int columnCount)
{
    int i;

    if (row == NULL || row->values == NULL)
    {
        return;
    }

    for (i = 0; i < columnCount; i++)
    {
        free(row->values[i]);
    }

    free(row->values);
    row->values = NULL;
}

static int appendRowToTable(Table *table, char **values)
{
    Row *newRows;
    Row *row;
    int i;

    newRows = (Row *)realloc(table->rows, sizeof(Row) * (table->rowCount + 1));
    if (newRows == NULL)
    {
        return 0;
    }

    table->rows = newRows;
    row = &table->rows[table->rowCount];
    row->values = (char **)malloc(sizeof(char *) * table->columnCount);
    if (row->values == NULL)
    {
        return 0;
    }

    for (i = 0; i < table->columnCount; i++)
    {
        row->values[i] = csql_strdup(values[i]);
        if (row->values[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(row->values[i]);
            }
            free(row->values);
            row->values = NULL;
            return 0;
        }
    }

    table->rowCount++;
    return 1;
}

static int addTableLoaded(Database *db, Table *loadedTable)
{
    Table *newTables;

    newTables = (Table *)realloc(db->tables, sizeof(Table) * (db->tableCount + 1));
    if (newTables == NULL)
    {
        return 0;
    }

    db->tables = newTables;
    db->tables[db->tableCount] = *loadedTable;
    db->tableCount++;
    return 1;
}

static int saveTable(Table *table)
{
    FILE *file;
    char filePath[256];
    int i;
    int j;

    snprintf(filePath, sizeof(filePath), "%s/%s.tbl", DATA_DIR, table->name);
    file = fopen(filePath, "w"); /* REQUISITO: manipulacao de arquivo texto. */
    if (file == NULL)
    {
        printf("Erro: nao foi possivel salvar %s.\n", filePath);
        return 0;
    }

    fprintf(file, "CSQL_TABLE\n");
    fprintf(file, "name=%s\n", table->name);
    fprintf(file, "columns=%d\n", table->columnCount);

    for (i = 0; i < table->columnCount; i++)
    {
        fprintf(file, "%s|%s\n", table->columns[i].name, table->columns[i].type);
    }

    fprintf(file, "rows=%d\n", table->rowCount);

    for (i = 0; i < table->rowCount; i++)
    {
        for (j = 0; j < table->columnCount; j++)
        {
            fprintf(file, "%s", table->rows[i].values[j]);
            if (j < table->columnCount - 1)
            {
                fprintf(file, "|");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 1;
}

static int loadTableFromFile(Database *db, const char *filePath)
{
    FILE *file;
    Table table;
    char line[1024];
    char *separator;
    int i;
    int rowIndex;
    int rowCount;
    char **values;

    file = fopen(filePath, "r"); /* REQUISITO: manipulacao de arquivo texto. */
    if (file == NULL)
    {
        return 0;
    }

    table.name[0] = '\0';
    table.columns = NULL;
    table.columnCount = 0;
    table.rows = NULL;
    table.rowCount = 0;

    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return 0;
    }
    remove_newline(line);
    if (strcmp(line, "CSQL_TABLE") != 0)
    {
        fclose(file);
        return 0;
    }

    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return 0;
    }
    remove_newline(line);
    if (strncmp(line, "name=", 5) != 0)
    {
        fclose(file);
        return 0;
    }
    strncpy(table.name, line + 5, MAX_NAME - 1);
    table.name[MAX_NAME - 1] = '\0';

    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return 0;
    }
    remove_newline(line);
    if (sscanf(line, "columns=%d", &table.columnCount) != 1 || table.columnCount <= 0)
    {
        fclose(file);
        return 0;
    }

    table.columns = (Column *)malloc(sizeof(Column) * table.columnCount);
    if (table.columns == NULL)
    {
        fclose(file);
        return 0;
    }

    for (i = 0; i < table.columnCount; i++)
    {
        if (fgets(line, sizeof(line), file) == NULL)
        {
            freeTable(&table);
            fclose(file);
            return 0;
        }

        remove_newline(line);
        separator = strchr(line, '|');
        if (separator == NULL)
        {
            freeTable(&table);
            fclose(file);
            return 0;
        }

        *separator = '\0';
        strncpy(table.columns[i].name, line, MAX_NAME - 1);
        table.columns[i].name[MAX_NAME - 1] = '\0';
        strncpy(table.columns[i].type, separator + 1, MAX_TYPE - 1);
        table.columns[i].type[MAX_TYPE - 1] = '\0';
    }

    if (fgets(line, sizeof(line), file) == NULL)
    {
        freeTable(&table);
        fclose(file);
        return 0;
    }
    remove_newline(line);
    if (sscanf(line, "rows=%d", &rowCount) != 1 || rowCount < 0)
    {
        freeTable(&table);
        fclose(file);
        return 0;
    }

    for (rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        if (fgets(line, sizeof(line), file) == NULL)
        {
            freeTable(&table);
            fclose(file);
            return 0;
        }

        remove_newline(line);
        values = NULL;
        if (!parsePipeValues(line, &values, table.columnCount))
        {
            freeTable(&table);
            fclose(file);
            return 0;
        }

        if (!appendRowToTable(&table, values))
        {
            freeStringArray(values, table.columnCount);
            freeTable(&table);
            fclose(file);
            return 0;
        }

        freeStringArray(values, table.columnCount);
    }

    fclose(file);

    if (findTable(db, table.name) != NULL)
    {
        freeTable(&table);
        return 0;
    }

    if (!addTableLoaded(db, &table))
    {
        freeTable(&table);
        return 0;
    }

    return 1;
}

static int parsePipeValues(char *line, char ***values, int expectedCount)
{
    char **items;
    char *token;
    int count;

    items = (char **)malloc(sizeof(char *) * expectedCount);
    if (items == NULL)
    {
        return 0;
    }

    count = 0;
    token = strtok(line, "|");
    while (token != NULL && count < expectedCount)
    {
        items[count] = csql_strdup(token);
        if (items[count] == NULL)
        {
            freeStringArray(items, count);
            return 0;
        }
        count++;
        token = strtok(NULL, "|");
    }

    while (count < expectedCount)
    {
        items[count] = csql_strdup("");
        if (items[count] == NULL)
        {
            freeStringArray(items, count);
            return 0;
        }
        count++;
    }

    *values = items;
    return 1;
}

static void freeStringArray(char **values, int count)
{
    int i;

    if (values == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(values[i]);
    }

    free(values);
}

static void clearDatabase(Database *db)
{
    freeDatabase(db);
    initDatabase(db);
}

static void ensureDataDirectory(void)
{
    mkdir(DATA_DIR, 0777);
}

#ifndef DATABASE_H
#define DATABASE_H

#define MAX_NAME 50
#define MAX_TYPE 20
#define DATA_DIR "data"

/*
 * REQUISITO ACADEMICO: uso de structs para representar colunas,
 * linhas, tabelas e o banco de dados inteiro.
 */
typedef struct
{
    char name[MAX_NAME];
    char type[MAX_TYPE];
} Column;

typedef struct
{
    char **values; /* REQUISITO: vetor dinamico de strings. */
} Row;

typedef struct
{
    char name[MAX_NAME];
    Column *columns; /* REQUISITO: memoria dinamica com malloc/realloc/free. */
    int columnCount;

    Row *rows; /* REQUISITO: registros armazenados dinamicamente. */
    int rowCount;
} Table;

typedef struct
{
    Table *tables; /* REQUISITO: tabelas armazenadas dinamicamente. */
    int tableCount;
} Database;

void initDatabase(Database *db);
void freeDatabase(Database *db);
Table *findTable(Database *db, const char *name);

int createTable(Database *db, const char *tableName, char **columnNames, int columnCount);
int insertRow(Database *db, const char *tableName, char **values, int valueCount);
int selectRows(Database *db, const char *tableName, const char *columnName);
int deleteRows(Database *db, const char *tableName, const char *whereColumn, const char *whereValue);
int updateRows(Database *db, const char *tableName, const char *setColumn, const char *setValue,
               const char *whereColumn, const char *whereValue);
int innerJoin(Database *db, const char *leftTableName, const char *rightTableName,
              const char *leftColumnName, const char *rightColumnName);

void showTables(Database *db);
void createDemo(Database *db);

int saveDatabase(Database *db);
int loadDatabase(Database *db);

#endif

# CSQL - Cria SQL

Mini banco de dados relacional em C para terminal.

## Compilar

```bash
gcc *.c -o csql
```

Ou, com avisos:

```bash
gcc -Wall -Wextra -pedantic *.c -o csql
```

## Rodar

```bash
./csql
```

Digite `HELP` dentro do programa para ver os comandos.

## Comando rapido para apresentacao

```sql
DEMO
SELECT * FROM usuarios
SELECT * FROM pedidos
SELECT * FROM usuarios JOIN pedidos ON usuarios.id = pedidos.user_id
```

Os dados sao salvos em arquivos texto dentro da pasta `data/`.

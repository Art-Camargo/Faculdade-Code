#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *csql_strdup(const char *text)
{
    char *copy;

    if (text == NULL)
    {
        return NULL;
    }

    copy = (char *)malloc(strlen(text) + 1); /* REQUISITO: memoria alocada dinamicamente. */
    if (copy != NULL)
    {
        strcpy(copy, text);
    }

    return copy;
}

void remove_newline(char *text)
{
    int i;

    if (text == NULL)
    {
        return;
    }

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n' || text[i] == '\r')
        {
            text[i] = '\0';
            return;
        }
    }
}

void trim(char *text)
{
    int start;
    int end;
    int i;

    if (text == NULL)
    {
        return;
    }

    start = 0;
    while (text[start] != '\0' && isspace((unsigned char)text[start]))
    {
        start++;
    }

    end = (int)strlen(text) - 1;
    while (end >= start && isspace((unsigned char)text[end]))
    {
        end--;
    }

    i = 0;
    while (start <= end)
    {
        text[i] = text[start];
        i++;
        start++;
    }
    text[i] = '\0';
}

int starts_with_ignore_case(const char *text, const char *prefix)
{
    int i;

    if (text == NULL || prefix == NULL)
    {
        return 0;
    }

    for (i = 0; prefix[i] != '\0'; i++)
    {
        if (text[i] == '\0')
        {
            return 0;
        }
        if (toupper((unsigned char)text[i]) != toupper((unsigned char)prefix[i]))
        {
            return 0;
        }
    }

    return 1;
}

int equals_ignore_case(const char *a, const char *b)
{
    int i;

    if (a == NULL || b == NULL)
    {
        return 0;
    }

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++)
    {
        if (toupper((unsigned char)a[i]) != toupper((unsigned char)b[i]))
        {
            return 0;
        }
    }

    return a[i] == '\0' && b[i] == '\0';
}

void to_upper_string(char *text)
{
    int i;

    if (text == NULL)
    {
        return;
    }

    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = (char)toupper((unsigned char)text[i]);
    }
}

int is_valid_name(const char *name)
{
    int i;

    if (name == NULL || name[0] == '\0')
    {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalnum((unsigned char)name[i]) && name[i] != '_')
        {
            return 0;
        }
    }

    return 1;
}

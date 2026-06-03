#ifndef UTILS_H
#define UTILS_H

char *csql_strdup(const char *text);
void trim(char *text);
void remove_newline(char *text);
int starts_with_ignore_case(const char *text, const char *prefix);
int equals_ignore_case(const char *a, const char *b);
void to_upper_string(char *text);
int is_valid_name(const char *name);

#endif

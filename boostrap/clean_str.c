/*
** EPITECH PROJECT, 2018
** Clean strings
** File description:
** Cleaner of string for Minishell2
*/

#include <stdlib.h>
#include <string.h>

char *replace_all(char *str, char to_replace, char replace_by)
{
    for (int i = 0 ; str[i] ; i++) {
        if (str[i] == to_replace)
            str[i] = replace_by;
    }
    return (str);
}

int count_begin(char *str)
{
    int len = 0;

    for (int i = 0; str[i] ; i++) {
        if (!((str[i] == ' ' || str[i] == '\t') && len == 0))
            len++;
    }
    return (len);
}

char *clean_spaces_tabs(char *str)
{
    char *new_str = NULL;
    int len = count_begin(str);
    int last_char_i = 0;
    int index = 0;
    int base_len = strlen(str);

    for (int i = base_len - 1;
        str[i] == ' ' || str[i] == '\t' || str[i] == 10; i--)
        last_char_i++;
    len -= last_char_i;
    new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
        exit(84);
    new_str[len] = '\0';
    for (int i = 0 ; i < base_len - last_char_i ; i++) {
        if (!((str[i] == ' ' || str[i] == '\t' || str[i] == 10) && index == 0))
            new_str[index++] = str[i];
    }
    new_str = replace_all(new_str, '\t', ' ');
    return (new_str);
}
/*
** EPITECH PROJECT, 2018
** Clean strings
** File description:
** Cleaner of string for Minishell2
*/

#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>

int is_banned_char(char c)
{
    if (c == ' ' || c == '\t' || c == 10)
        return (1);
    return (0);
}

int count_leading(char *str)
{
    int len = 0;

    for (; is_banned_char(str[len]); len++);
    return (len);
}

int count_trailing(char *str)
{
    int len = strlen(str) - 1;

    if (len > 0)
        for (; is_banned_char(str[len]); len--);
    return (len);
}

void complete_string(char *src, char *dest, int begin_len, int end_len)
{
    int index = 0;

    for (int i = begin_len; src[i] && i < (begin_len + end_len); i++) {
        if (src[i] == ' ' && is_banned_char(src[i + 1]))
            continue;
        dest[index++] = src[i];
    }
    dest[index] = '\0';
}

char *clean_string(char *str)
{
    char *new_str = NULL;
    int begin_len = count_leading(str);
    int end_len = count_trailing(str) + 1;
    int len = (end_len - begin_len);

    for (int i = begin_len; str[i] && i < end_len; i++) {
        if ((str[i] == ' ' && is_banned_char(str[i + 1]))
            || str[i] == '\t' || str[i] == 10)
            len--;
    }
    new_str = malloc(sizeof(char) * (len + 2));
    if (!new_str) {
        free(str);
        exit(84);
    }
    complete_string(str, new_str, begin_len, end_len);
    free(str);
    return (new_str);
}
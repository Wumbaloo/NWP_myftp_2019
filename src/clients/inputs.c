/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Where inputs of clients are handled
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *remove_crlf(char *string, int valread)
{
    int new_valread = valread;
    char *new_string = NULL;

    if (string[valread - 1] == 10) {
        string[valread - 2] = '\0';
        new_valread--;
    }
    if (string[valread - 2] == 13) {
        string[valread - 3] = '\0';
        new_valread--;
    }
    if (new_valread != valread) {
        new_string = malloc(sizeof(char) * (new_valread + 1));
        if (!new_string)
            exit(84);
        memcpy(new_string, string, new_valread);
        new_string[new_valread] = '\0';
        free(string);
        return (new_string);
    }
    return (string);
}

void get_input(int fd, char **input)
{
    char buffer[1024];
    char end_buffer[1024];
    int valread = -1;
    int len = 0;

    memset(end_buffer, 0, 1024);
    memset(buffer, 0, 1024);
    do {
        valread = read(fd, buffer, 1024);
        buffer[valread] = '\0';
        strncat(end_buffer, buffer, valread);
        len += valread;
    } while (valread <= 2 ||
            (buffer[valread - 1] != 10 && buffer[valread - 2] != 13));
    end_buffer[len] = '\0';
    (*input) = malloc(sizeof(char) * (len + 1));
    if (*input == NULL)
        exit(84);
    memcpy((*input), end_buffer, len + 1);
    (*input) = remove_crlf((*input), len);
}

char *read_from_client(int fd)
{
    char *string = NULL;
    get_input(fd, &string);

    return (string);
}
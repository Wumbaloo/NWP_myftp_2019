/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** CWD command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "ftp.h"

char *get_folder(char *input)
{
    char cwd[PATH_MAX];

    if (chdir(input) == 0) {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
            return (NULL);
        return (strdup(cwd));
    }
    return (NULL);
}

void cwd_cmd(client_t *client, void *input)
{
    char *command = strdup(input);
    char *txt = strtok(input, " ");

    if (txt)
        txt = strtok(NULL, " ");
    txt = get_folder(txt);
    if (!txt)
        client_answer(client, 550, "Failed to change directory.");
    else {
        free(client->pwd);
        client->pwd = strdup(txt);
        client_answer(client, 250, client->pwd);
    }
}

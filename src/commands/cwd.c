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

char *get_folder(char *base, char *input)
{
    char oldcwd[PATH_MAX];
    char cwd[PATH_MAX];
    size_t len_base = strlen(base);

    if (base[len_base - 1] == '/')
        len_base--;
    if (getcwd(oldcwd, sizeof(oldcwd)) == NULL)
        return (NULL);
    if (!input)
        return (NULL);
    else if (chdir(input) == 0) {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
            return (NULL);
        else if (strncmp(cwd, base, len_base) != 0) {
            chdir(oldcwd);
            return (NULL);
        }
        return (strdup(cwd));
    }
    return (NULL);
}

void cwd_cmd(client_t *client, void *input, ftp_t *ftp)
{
    char *command = strdup(input);
    char *txt = strtok(input, " ");

    if (txt)
        txt = strtok(NULL, " ");
    txt = get_folder(ftp->pwd, txt);
    if (!txt)
        client_answer(client, 550, "Failed to change directory.");
    else {
        free(client->pwd);
        client->pwd = strdup(txt);
        client_answer(client, 250, client->pwd);
    }
}

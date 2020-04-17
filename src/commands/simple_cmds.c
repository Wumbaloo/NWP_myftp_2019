/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Simple commands implementation
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "ftp.h"

void noop_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 200, "NOOP.");
}

void help_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 214, "This FTP works perfectly! I think so...");
}

void cwd_cmd(client_t *client, void *input)
{
    char *command = strdup(input);
    char *txt = strtok(input, " ");

    if (txt)
        txt = strtok(NULL, " ");
    if (!txt)
        client_answer(client, 501, "Syntax error in parameters.");
    else {
        if (!does_folder_exists(txt)) {
            client_answer(client, 550, "Failed to change directory.");
            return;
        }
        free(client->pwd);
        client->pwd = strdup(txt);
        client_answer(client, 250, client->pwd);
    }
}

void pwd_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 257, client->pwd);
}

void delete_file_cmd(client_t *client, void *input)
{
    char *command = strdup(input);
    char *txt = strtok(input, " ");

    if (txt)
        txt = strtok(NULL, " ");
    if (!txt)
        client_answer(client, 501, "Syntax error in parameters.");
    else {
        if (access(txt, F_OK) == -1 || remove(txt) != 0) {
            client_answer(client, 550,
                    "File unavailable (e.g., file not found, no access).");
            return;
        }
        client_answer(client, 250, "Requested file action okay, completed.");
    }
}
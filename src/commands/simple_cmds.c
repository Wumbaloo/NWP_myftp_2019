/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Simple commands implementation
*/

#include <stdlib.h>
#include <string.h>
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
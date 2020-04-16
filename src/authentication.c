/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Authentication management
*/

#include <stdlib.h>
#include <string.h>
#include "clients.h"
#include "ftp.h"

void set_username(client_t *client, void *cmd)
{
    char *command = strdup(cmd);
    char *txt = strtok(cmd, " ");

    if (txt)
        txt = strtok(NULL, " ");
    if (!txt || (txt && strncmp(txt, "Anonymous", 9) != 0))
        client_answer(client, 430, "Unknown acount.");
    else
        client_answer(client, 331, "Set username correctly.");
}

void set_password(client_t *client, void *cmd)
{
    char *command = strdup(cmd);
    char *txt = strtok(cmd, " ");

    txt = strtok(NULL, " ");
    if (txt && (txt[0] != 13 && txt[0] != '\n'))
        client_answer(client, 430, "Bad password.");
    else
        client_answer(client, 230, "Successful login.");
}

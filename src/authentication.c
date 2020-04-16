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
    client->is_logged = 0;
    if (!txt || (txt && strncmp(txt, "Anonymous", 9) != 0))
        client_answer(client, 430, "Unknown acount.");
    else {
        client_answer(client, 331, "User name okay, need password.");
        client->is_logged = -1;
    }
}

void set_password(client_t *client, void *cmd)
{
    char *command = strdup(cmd);
    char *txt = strtok(cmd, " ");

    txt = strtok(NULL, " ");
    if (txt && (txt[0] != 13 && txt[0] != '\n'))
        client_answer(client, 430, "Bad password.");
    else if (client->is_logged != -1)
        client_answer(client, 332, "Need account for login");
    else {
        client_answer(client, 230, "User logged in.");
        client->is_logged = 1;
    }
}

/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Commands handler
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ftp.h"

void noop_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 200, "NOOP.");
}

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

void handle_command(client_t *client, char *input, fd_set *active_fd_set)
{
    char *base_input = strdup(input);
    char *cmd = strtok(input, " ");

    if (!client)
        return;
    if (!cmd)
        cmd = input;
    for (int i = 0 ; myftp->cmds[i] ; i++) {
        if (strcmp(myftp->cmds[i]->command, cmd) == 0) {
            if (i == 0)
                myftp->cmds[i]->func(client, active_fd_set);
            else
                myftp->cmds[i]->func(client, base_input);
            free(base_input);
            return;
        }
    }
    client_answer(client, 500, "What's next?");
    free(base_input);
}

void free_commands(void)
{
    for (int i = 0; myftp->cmds[i]; i++) {
        free(myftp->cmds[i]->command);
        free(myftp->cmds[i]);
    }
    free(myftp);
}
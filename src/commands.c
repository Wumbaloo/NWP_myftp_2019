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

void pasv_command(client_t *client, void *arg)
{
    printf("PASV from: %s.\n", inet_ntoa(client->data.sin_addr));
}

void set_username(client_t *client, void *cmd)
{
    char *command = strdup(cmd);
    char *text = strtok(cmd, " ");
    int len;

    if (text)
        text = strtok(NULL, " ");
    len = strlen(text);
    if (text[len - 1] == 13 || text[len - 1] == '\n')
        text[len - 1] = '\0';
    if (!text || strncmp(text, "Anonymous", 9) != 0) {
        dprintf(client->fd, "430\n");
        printf("Client %d tried to set a new username\n", client->fd);
    } else {
        dprintf(client->fd, "331\n");
        printf("Client %d has a new username which is %s\n", client->fd, text);
    }
}

void set_password(client_t *client, void *cmd)
{
    char *command = strdup(cmd);
    char *text = strtok(cmd, " ");

    text = strtok(NULL, " ");
    if (text && (text[0] != 13 && text[0] != '\n')) {
        dprintf(client->fd, "430\n");
        printf("Client %d tried to set a new password\n", client->fd);
    } else{
        dprintf(client->fd, "230\n");
        printf("Client %d has a new password which is %s\n", client->fd, text);
    }
}

void handle_command(client_t *client, char *input, fd_set *active_fd_set)
{
    char *base_input = strdup(input);
    char *cmd = strtok(input, " ");

    if (!client)
        printf("HERE\n");
    if (!cmd)
        cmd = input;
    for (int i = 0 ; myftp->cmds[i] ; i++) {
        if (strcmp(myftp->cmds[i]->command, cmd) == 0) {
            if (strcmp(cmd, "exit") == 0)
                myftp->cmds[i]->func(client, active_fd_set);
            else
                myftp->cmds[i]->func(client, base_input);
            free(base_input);
            return;
        }
    }
    dprintf(client->fd, "Server: What's next?\n");
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
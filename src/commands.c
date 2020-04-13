/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Commands handler
*/

#include <stdio.h>
#include <string.h>
#include "ftp.h"

void set_username(int clientfd, void *username)
{
    dprintf(clientfd, "331\n");
    printf("Client %d has a new username\n", clientfd);
}

void set_password(int clientfd, void *password)
{
    dprintf(clientfd, "230\n");
    printf("Client %d has a new password\n", clientfd);
}

void handle_command(int clientfd, char *input, fd_set *active_fd_set)
{
    char *cmd = strtok(input, " ");

    if (!cmd)
        cmd = input;
    for (int i = 0 ; myftp->cmds[i] ; i++) {
        if (strcmp(myftp->cmds[i]->command, cmd) == 0) {
            myftp->cmds[i]->func(clientfd, active_fd_set);
            return;
        }
    }
    dprintf(clientfd, "Server: What's next?\n");
}

void free_commands(void)
{
    for (int i = 0; myftp->cmds[i]; i++) {
        free(myftp->cmds[i]->command);
        free(myftp->cmds[i]);
    }
    free(myftp);
}
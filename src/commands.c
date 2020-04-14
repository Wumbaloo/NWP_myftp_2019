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

void pasv_command(int clientfd, void *arg)
{
    printf("PASV\n");
}

void set_username(int clientfd, void *cmd)
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
        dprintf(clientfd, "430\n");
        printf("Client %d tried to set a new username\n", clientfd);
    } else {
        dprintf(clientfd, "331\n");
        printf("Client %d has a new username which is %s\n", clientfd, text);
    }
}

void set_password(int clientfd, void *cmd)
{
    char *command = strdup(cmd);
    char *text = strtok(cmd, " ");

    text = strtok(NULL, " ");
    if (text && (text[0] != 13 && text[0] != '\n')) {
        dprintf(clientfd, "430\n");
        printf("Client %d tried to set a new password\n", clientfd);
    } else{
        dprintf(clientfd, "230\n");
        printf("Client %d has a new password which is %s\n", clientfd, text);
    }
}

void handle_command(int clientfd, char *input, fd_set *active_fd_set)
{
    char *base_input = strdup(input);
    char *cmd = strtok(input, " ");

    if (!cmd)
        cmd = input;
    for (int i = 0 ; myftp->cmds[i] ; i++) {
        if (strcmp(myftp->cmds[i]->command, cmd) == 0) {
            if (strcmp(cmd, "exit") == 0)
                myftp->cmds[i]->func(clientfd, active_fd_set);
            else
                myftp->cmds[i]->func(clientfd, base_input);
            free(base_input);
            return;
        }
    }
    dprintf(clientfd, "Server: What's next?\n");
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
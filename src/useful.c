/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Useful functions for the FTP
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ftp.h"

void client_answer(client_t *client, int code, char *msg)
{
    dprintf(client->fd, "%d %s\r\n", code, msg);
    printf("Client %d: %d\r\n", client->fd, code);
}

void close_connection(client_t *client, void *active_fd_set)
{
    client_answer(client, 221, "Service closing control connection.");
    close(client->fd);
    client->is_logged = 0;
    FD_CLR(client->fd, (fd_set *) active_fd_set);
}

int does_file_exists(char *path)
{
    if (access(path, F_OK) != -1)
        return (1);
    return (0);
}
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

void close_connection(client_t *client, void *active_fd_set)
{
    close(client->fd);
    printf("Close connection\n");
    client->is_logged = 0;
    FD_CLR(client->fd, (fd_set *) active_fd_set);
}

void client_answer(client_t *client, int code, char *msg)
{
    dprintf(client->fd, "%d %s\r\n", code, msg);
    printf("Client %d: %d\r\n", client->fd, code);
}
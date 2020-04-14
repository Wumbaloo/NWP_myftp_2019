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
    FD_CLR(client->fd, (fd_set *) active_fd_set);
}

void close_all_connections(int sig)
{
    fd_set active_fd_set;
    fd_set total_fd_set;

    (void)(sig);
    FD_SET(myftp->serverfd, &total_fd_set);
    for (int i = 0; i < FD_SETSIZE; i++) {
        active_fd_set = total_fd_set;
        if (!FD_ISSET(i, &active_fd_set) || i == myftp->serverfd)
            continue;
        write(i, "Server stopped the connection.", 1024);
        close(i);
        FD_CLR(i, &active_fd_set);
    }
    exit(0);
}

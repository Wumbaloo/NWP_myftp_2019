/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Core of the server
*/

#include <stdlib.h>
#include <signal.h>
#include "ftp.h"

int loop_server(int serverfd)
{
    fd_set active_fd_set;

    signal(SIGINT, close_all_connections);
    FD_ZERO(&active_fd_set);
    FD_SET(serverfd, &active_fd_set);
    for (;;) {
        myftp->read_fd_set = active_fd_set;
        int nready = select(FD_SETSIZE, &myftp->read_fd_set, NULL, NULL, &myftp->timeout);
        if (nready <= 0)
            continue;
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, &myftp->read_fd_set))
                continue;
            else if (treat_potential_client(serverfd, i, &active_fd_set) != 0)
                return (84);
        }
    }
}

int launch_server(int ac, char **av)
{
    char *path = NULL;
    int port = -1;
    int serverfd = -1;

    if (ac != 3)
        return (84);
    port = strtol(av[1], NULL, 10);
    path = av[2];
    if (port < 0)
        return (84);
    serverfd = create_server(port);
    if (serverfd < 0)
        return (84);
    myftp = malloc(sizeof(ftp_t));
    if (myftp == NULL)
        return (84);
    myftp->timeout.tv_sec = 1;
    myftp->timeout.tv_usec = myftp->timeout.tv_sec * 1000;
    myftp->serverfd = serverfd;
    loop_server(serverfd);
    return (0);
}
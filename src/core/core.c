/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Core of the server
*/

#include <stdlib.h>
#include <signal.h>
#include "commands.h"
#include "ftp.h"

int loop_server(int serverfd, ftp_t *ftp)
{
    fd_set active_fd_set;

    initialize_commands(ftp);
    FD_ZERO(&active_fd_set);
    FD_SET(serverfd, &active_fd_set);
    for (;;) {
        ftp->read_fd_set = active_fd_set;
        int nready = select(FD_SETSIZE, &ftp->read_fd_set, NULL, NULL,
            &ftp->timeout);
        if (nready <= 0)
            continue;
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, &ftp->read_fd_set))
                continue;
            else if (treat_client(serverfd, i, &active_fd_set, ftp) != 0)
                return (84);
        }
    }
    free_ftp(ftp);
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
    ftp_t *ftp = malloc(sizeof(ftp_t));
    if (ftp == NULL)
        return (84);
    ftp->timeout.tv_sec = 1;
    ftp->timeout.tv_usec = ftp->timeout.tv_sec * 1000;
    ftp->serverfd = serverfd;
    loop_server(serverfd, ftp);
    return (0);
}
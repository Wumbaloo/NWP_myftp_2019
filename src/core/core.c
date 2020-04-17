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
    fd_set read_fd_set;
    int nready = -1;

    initialize_commands(ftp);
    FD_ZERO(&active_fd_set);
    FD_SET(serverfd, &active_fd_set);
    for (;;) {
        read_fd_set = active_fd_set;
        nready = select(FD_SETSIZE, &read_fd_set, NULL, NULL,
            &ftp->timeout);
        if (nready <= 0)
            continue;
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, &read_fd_set))
                continue;
            else if (treat_client(serverfd, i, &active_fd_set, ftp) != 0)
                return (84);
        }
    }
    free_ftp(ftp);
}

ftp_t *create_ftp(char *path, int port, int serverfd)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));

    if (ftp == NULL)
        return (NULL);
    ftp->pwd = path;
    ftp->timeout.tv_sec = 1;
    ftp->timeout.tv_usec = ftp->timeout.tv_sec * 1000;
    ftp->serverfd = serverfd;
    return (ftp);
}

int launch_server(int ac, char **av)
{
    int port = -1;
    int serverfd = -1;
    ftp_t *ftp = NULL;

    if (ac != 3)
        return (84);
    port = strtol(av[1], NULL, 10);
    if (port < 0 || port > 65535)
        return (84);
    else if (!does_folder_exists(av[2]))
        return (84);
    serverfd = create_server(port);
    if (serverfd < 0)
        return (84);
    ftp = create_ftp(av[2], port, serverfd);
    if (!ftp)
        return (84);
    loop_server(serverfd, ftp);
    return (0);
}
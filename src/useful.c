/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Useful functions for the FTP
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "ftp.h"

void client_answer(client_t *client, int code, char *msg)
{
    dprintf(client->fd, "%d %s\r\n", code, msg);
    printf("Client %d: %d\r\n", client->fd, code);
}

void close_connection(client_t *client, void *active_fd_set)
{
    client_answer(client, 221, "Service closing control connection.");
    if (client->data_socket != -1)
        close(client->data_socket);
    close(client->fd);
    client->is_logged = 0;
    FD_CLR(client->fd, (fd_set *) active_fd_set);
}

int does_folder_exists(char *path)
{
    struct stat path_stat;
    DIR *dir = NULL;

    if (stat(path, &path_stat) != 0)
        return (0);
    else if (access(path, F_OK) == -1)
        return (0);
    dir = opendir(path);
    if (dir == NULL)
        return (0);
    return (S_ISDIR(path_stat.st_mode));
}
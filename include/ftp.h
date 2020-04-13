/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** FTP header file
*/

#ifndef MY_FTP_H__
#define MY_FTP_H__

#include <stddef.h>
#include <sys/time.h>

int create_server(int port);
int launch_server(int ac, char **av);
int treat_potential_client(int serverfd, int i, fd_set *active_fd_set);

void close_all_connections(int sig);

typedef struct ftp_s {
    int serverfd;
    fd_set read_fd_set;
    struct timeval timeout;
} ftp_t;

extern ftp_t *myftp;

#endif
/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Structs header file
*/

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stddef.h>
#include <sys/time.h>
#include <arpa/inet.h>

typedef struct client_s {
    int fd;
    int data_socket;
    int is_logged;
    struct sockaddr_in config_socket;
    struct sockaddr_in data;
    struct client_s *next;
} client_t;

typedef struct command_s {
    int need_login;
    char *command;
    void (*func)(client_t *, void *);
} command_t;

typedef struct ftp_s {
    int serverfd;
    char *pwd;
    fd_set read_fd_set;
    struct timeval timeout;
    command_t **cmds;
    client_t *client_head;
} ftp_t;

#endif
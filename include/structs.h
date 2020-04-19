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
    int data_fd;
    int is_logged;
    char *pwd;
    struct sockaddr_in config_socket;
    struct sockaddr_in data;
    struct client_s *next;
} client_t;

typedef struct ftp_s {
    int serverfd;
    char *pwd;
    struct timeval timeout;
    struct command_s **cmds;
    client_t *client_head;
} ftp_t;

typedef struct command_s {
    int need_login;
    char *command;
    void (*func)(client_t *, void *, ftp_t *ftp);
} command_t;

#endif
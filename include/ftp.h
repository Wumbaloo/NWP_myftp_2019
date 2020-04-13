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

void close_connection(int clientfd, void *active_fd_set);
void close_all_connections(int sig);

void handle_command(int clientfd, char *input, fd_set *active_fd_set);
void set_username(int clientfd, void *username);
void set_password(int clientfd, void *password);
void initialize_commands(void);
void free_commands(void);

typedef struct command_s {
    char *command;
    void (*func)(int, void *);
} command_t;

typedef struct ftp_s {
    int serverfd;
    fd_set read_fd_set;
    struct timeval timeout;
    command_t **cmds;
} ftp_t;

extern ftp_t *myftp;

#endif
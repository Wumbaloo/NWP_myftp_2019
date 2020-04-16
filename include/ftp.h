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
#include <arpa/inet.h>
#include "client_list.h"

int create_server(int port);
int launch_server(int ac, char **av);
int treat_potential_client(int serverfd, int i, fd_set *active_fd_set,
                            client_t **head);

void close_connection(client_t *client, void *active_fd_set);
void client_answer(client_t *client, int code, char *msg);

void handle_command(client_t *client, char *input, fd_set *active_fd_set);
void set_username(client_t *client, void *username);
void set_password(client_t *client, void *password);
void pasv_command(client_t *client, void *arg);
void noop_cmd(client_t *client, void *arg);
void initialize_commands(void);
void free_commands(void);

typedef struct command_s {
    char *command;
    void (*func)(client_t *, void *);
} command_t;

typedef struct ftp_s {
    int serverfd;
    fd_set read_fd_set;
    struct timeval timeout;
    command_t **cmds;
    client_t *client_head;
} ftp_t;

extern ftp_t *myftp;

#endif
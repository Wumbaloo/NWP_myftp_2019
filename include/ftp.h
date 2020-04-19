/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** FTP header file
*/

#ifndef MY_FTP_H__
#define MY_FTP_H__

#include "structs.h"

char *read_from_client(int fd);

int create_server(int port);
int does_folder_exists(char *path);
int launch_server(int ac, char **av);
int treat_client(int serverfd, int i, fd_set *active, ftp_t *ftp);

void close_connection(client_t *client, void *active_fd_set, ftp_t *ftp);
void client_answer(client_t *client, int code, char *msg);

void set_username(client_t *client, void *username, ftp_t *ftp);
void set_password(client_t *client, void *password, ftp_t *ftp);
void pasv_command(client_t *client, void *arg, ftp_t *ftp);

void free_ftp(ftp_t *ftp);

struct sockaddr_in setup_server_config(int sockfd, int port);

#endif
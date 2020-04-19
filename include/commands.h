/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Commands include file
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "structs.h"

void handle_command(client_t *client, char *input, fd_set *active, ftp_t *ftp);
void noop_cmd(client_t *client, void *arg, ftp_t *ftp);
void help_cmd(client_t *client, void *arg, ftp_t *ftp);
void cwd_cmd(client_t *client, void *arg, ftp_t *ftp);
void pwd_cmd(client_t *client, void *arg, ftp_t *ftp);
void delete_file_cmd(client_t *client, void *input, ftp_t *ftp);

void initialize_commands(ftp_t *ftp);

#endif
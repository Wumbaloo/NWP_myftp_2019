/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Where the ftp is initialized
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "ftp.h"

ftp_t *myftp = NULL;

struct sockaddr_in setup_server_config(int sockfd, int port)
{
    int opt = 1;
    struct sockaddr_in config;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(84);
    }
    config.sin_family = AF_INET;
    config.sin_addr.s_addr = INADDR_ANY;
    config.sin_port = htons(port);
    return (config);
}

int create_server(int port)
{
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in config;

    if (serverfd == -1) {
        perror("socket");
        return (-1);
    }
    config = setup_server_config(serverfd, port);
    if (bind(serverfd, (struct sockaddr *) &config,
        sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        return (-1);
    }
    if (listen(serverfd, 5) < 0) {
        perror("listen");
        return (-1);
    }
    return (serverfd);
}

command_t *create_command(char *name, void (*ptr)(int, void *))
{
    command_t *cmd = malloc(sizeof(command_t));
    int len = strlen(name);

    if (cmd == NULL) {
        perror("command");
        exit(84);
    }
    cmd->command = malloc(sizeof(char) * (len + 1));
    if (cmd->command == NULL) {
        perror("command");
        exit(84);
    }
    strcpy(cmd->command, name);
    cmd->command[len] = '\0';
    cmd->func = ptr;
    return (cmd);
}

void initialize_commands(void)
{
    myftp->cmds = malloc(sizeof(command_t *) * 4);

    if (myftp->cmds == NULL) {
        perror("malloc");
        exit(84);
    }
    myftp->cmds[0] = create_command("exit", &close_connection);
    myftp->cmds[1] = create_command("USER", &set_username);
    myftp->cmds[2] = create_command("PASS", &set_password);
    myftp->cmds[3] = NULL;
}
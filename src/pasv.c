/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Passive mode management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include "ftp.h"

unsigned int get_port(int fd)
{
    struct sockaddr_in addr;
    int len = -1;
    unsigned int port = 0;

    bzero(&addr, sizeof(addr));
    len = sizeof(addr);
    getsockname(fd, (struct sockaddr *) &addr, &len);
    port = ntohs(addr.sin_port);
    return (port);
}

void pasv_send_client_instructions(client_t *client, unsigned int port)
{
    char *ip = inet_ntoa(client->data.sin_addr);
    char *ip1 = strtok(ip, ".");
    char *ip2 = strtok(NULL, ".");
    char *ip3 = strtok(NULL, ".");
    char *ip4 = strtok(NULL, ".");

    dprintf(client->fd, "%d Entering Passive Mode ", 227);
    dprintf(client->fd, "(%s, %s, %s, %s, %u, %d)\r\n",
        ip1, ip2, ip3, ip4, port, 256);
    printf("PASV from: %s.\n", ip);
}

void pasv_treat_new_client(client_t **client)
{
    struct sockaddr_in config;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    (*client)->data_fd = accept((*client)->data_socket,
                        (struct sockaddr *) &config, &addr_size);
    if ((*client)->data_fd < 0) {
        perror("accept");
        exit(84);
    }
    dprintf((*client)->data_fd, "220 Welcome PASV sub-client.\r\n");
}

void pasv_split_tasks(client_t *client, int port, int pip[2])
{
    pid_t forkpid = fork();

    if (forkpid == (pid_t) 0) {
        if (bind(client->data_socket, (struct sockaddr *)
            &client->config_socket, sizeof(struct sockaddr_in)) < 0) {
                perror("bind");
                exit(84);
        }
        close(pip[0]);
        if (listen(client->data_socket, 1) < 0) {
            perror("listen");
            exit(84);
        }
        pasv_treat_new_client(&client);
    } else {
        pasv_send_client_instructions(client, port);
    }
}

void pasv_command(client_t *client, void *arg, ftp_t *ftp)
{
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    unsigned int port = get_port(client->fd) / 256;
    int pip[2];

    (void) (ftp);
    if (pipe(pip)) {
        perror("pipe");
        exit(84);
    }
    if (client->data_socket == -1) {
        perror("socket");
        exit(84);
    }
    client->config_socket = setup_server_config(client->data_socket,
                                                (port * 256) + 256);
    pasv_split_tasks(client, port, pip);
}

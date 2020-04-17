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

void pasv_treat_new_client(client_t *client)
{
    struct sockaddr_in config;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char *str = NULL;
    int forkid = -1;
    int fd = accept(client->data_socket, (struct sockaddr *) &config,
                    &addr_size);
    if (fd < 0) {
        perror("accept");
        exit(84);
    }
    dprintf(fd, "220 Welcome PASV sub-client.");
    forkid = fork();
    if (forkid == 0) {
        str = read_from_client(fd);
        close(fd);
    }
}

void pasv_command(client_t *client, void *arg)
{
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    unsigned int port = get_port(client->fd);

    if (client->data_socket == -1) {
        perror("socket");
        exit(84);
    }
    client->config_socket = client->data;
    client->config_socket.sin_port = htons(port + 256);
    if (bind(client->data_socket, (struct sockaddr *) &client->config_socket,
        sizeof(struct sockaddr_in)) < 0) {
            perror("bind");
            exit(84);
    }
    if (listen(client->data_socket, 1) < 0) {
        perror("listen");
        exit(84);
    }
    pasv_send_client_instructions(client, port);
    pasv_treat_new_client(client);
}

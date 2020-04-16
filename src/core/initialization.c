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

/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client side of My FTP
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *clean_spaces_tabs(char *str);

int try_connect(char *ip, int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in config;

    if (sockfd == -1) {
        perror("socket");
        return (-1);
    }
    config.sin_family = AF_INET;
    config.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &config.sin_addr) <= 0) { 
        write(2, "Invalid address.\n", 17);
        return (-1);
    }
    if (connect(sockfd, (struct sockaddr *) &config, sizeof(config)) < 0) {
        perror("connect");
        return (-1);
    }
    return (sockfd);
}

int main(int ac, char **av)
{
    char *ip = NULL;
    int port = 8000;
    int sockfd = -1;
    char buffer[1024];
    char *input = NULL;
    size_t len = 0;
    int valread = -1;

    if (ac != 3)
        return (84);
    ip = av[1];
    port = strtol(av[2], NULL, 10);
    sockfd = try_connect(ip, port);
    if (sockfd < 0)
        return (84);
    valread = read(sockfd, buffer, 1024);
    if (valread == -1)
        return (84);
    printf("%s\n", buffer);
    do {
        getline(&input, &len, stdin);
        input = clean_spaces_tabs(input);
        write(sockfd, input, len);
        valread = read(sockfd, buffer, 1024);
        if (valread == -1)
            return (84);
        printf("%s\n", buffer);
        if (strcmp(buffer, "exit") > 0)
            break;
    } while (strcmp(input, "exit") != 0);
    return (0);
}
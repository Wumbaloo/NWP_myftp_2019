/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Server side of FTP
*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int serverfd = 0;
fd_set read_fd_set;

struct sockaddr_in setup_server(int sockfd)
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
    config.sin_port = htons(5000);
    return (config);
}

int create_server() {
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in config;

    if (serverfd == -1) {
        perror("socket");
        return (-1);
    }
    config = setup_server(serverfd);
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

int accept_new_connection(int serverfd)
{
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in clientstruct;
    int clientfd = accept(serverfd, (struct sockaddr *) &clientstruct, &client_addr_size);

    if (clientfd < 0) {
        perror("accept");
        return (-1);
    }
    write(clientfd, "Server: Hello client!", 22);
    printf("A new client joined with IP: %s.\n", inet_ntoa(clientstruct.sin_addr));
    return (clientfd);
}

void close_all_connections(int sig)
{
    fd_set active_fd_set;
    int max = FD_SETSIZE;

    (void)(sig);
    for (int i = 0; i < max; i++) {
        active_fd_set = read_fd_set;
        if (!FD_ISSET(i, &active_fd_set) || i == serverfd)
            continue;
        write(i, "Server stopped the connection.", 1024);
        close(i);
        FD_CLR(i, &active_fd_set);
    }
    exit(0);
}

int treat_potential_client(int serverfd, int i, fd_set *active_fd_set)
{
    int valread = -1;
    int clientfd = -1;
    char buffer[1024];

    if (i == serverfd) {
        clientfd = accept_new_connection(serverfd);
        if (clientfd < 0)
            return (84);
        FD_SET(clientfd, active_fd_set);
    } else {
        valread = read(i, buffer, 1024);
        if (valread == -1)
            return (84);
        if (valread == 0 || strcmp(buffer, "exit") == 0) {
            close(i);
            FD_CLR(i, active_fd_set);
        }
        printf("Received: %s\n", buffer);
        write(i, "Server: What's next?", 21);
    }
    return (0);
}

int main(void)
{
    serverfd = create_server();
    fd_set active_fd_set;
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = timeout.tv_sec * 1000;

    if (serverfd < 0)
        return (84);
    signal(SIGINT, close_all_connections);
    FD_ZERO(&active_fd_set);
    FD_SET(serverfd, &active_fd_set);
    for (;;) {
        read_fd_set = active_fd_set;
        int nready = select(FD_SETSIZE, &read_fd_set, NULL, NULL, &timeout);
        if (nready <= 0)
            continue;
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (!FD_ISSET(i, &read_fd_set))
                continue;
            if (treat_potential_client(serverfd, i, &active_fd_set) != 0)
                return (84);
        }
    }
    return (0);
}
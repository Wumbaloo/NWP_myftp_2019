/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client handler
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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

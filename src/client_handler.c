/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client handler
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ftp.h"

int accept_new_connection(int serverfd, client_t **head)
{
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    client_t *client = NULL;

    client = malloc(sizeof(client_t));
    if (!client) {
        perror("malloc");
        exit(84);
    }
    client->fd = accept(serverfd, (struct sockaddr *) &client->data,
                    &client_addr_size);
    if (client->fd < 0) {
        perror("accept");
        return (-1);
    }
    client->next = NULL;
    write(client->fd, "220\n", 4);
    insert_new_node(head, client);
    printf("A new client joined with IP: %s.\n", inet_ntoa(client->data.sin_addr));
    return (client->fd);
}

char *read_from_client(int fd)
{
    int valread = -1;
    char buffer[1024];
    char *string = NULL;

    valread = read(fd, buffer, 1024);
    if (valread == 0) {
        valread = 4;
        strcpy(buffer, "exit");
    }
    string = malloc(sizeof(char) * (valread + 1));
    if (string == NULL) {
        perror("malloc");
        exit(84);
    }
    memcpy(string, buffer, valread);
    string[valread] = '\0';
    return (string);
}

int treat_potential_client(int serverfd, int i, fd_set *active_fd_set,
                            client_t **head)
{
    int clientfd = -1;
    char *buffer;

    if (i == serverfd) {
        clientfd = accept_new_connection(serverfd, head);
        if (clientfd < 0)
            return (84);
        FD_SET(clientfd, active_fd_set);
    } else {
        buffer = read_from_client(i);
        if (buffer == NULL)
            return (84);
        handle_command(get_client_by_id(*head, i), buffer, active_fd_set);
        printf("Received: %s\n", buffer);
    }
    return (0);
}

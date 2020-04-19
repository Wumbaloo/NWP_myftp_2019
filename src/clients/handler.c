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
#include "clients.h"
#include "commands.h"
#include "ftp.h"

client_t *create_client(char *pwd)
{
    client_t *client = NULL;

    client = malloc(sizeof(client_t));
    if (!client) {
        perror("malloc");
        exit(84);
    }
    client->is_logged = 0;
    client->data_socket = -1;
    client->data_fd = -1;
    client->pwd = strdup("/");
    client->next = NULL;
}

int accept_new_connection(int serverfd, client_t **head, char *pwd)
{
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    client_t *client = create_client(pwd);

    client->fd = accept(serverfd, (struct sockaddr *) &client->data,
                    &client_addr_size);
    if (client->fd < 0) {
        perror("accept");
        return (-1);
    }
    client_answer(client, 220, "Welcome client.");
    insert_new_node(head, client);
    printf("A new client joined with IP: %s.\n",
            inet_ntoa(client->data.sin_addr));
    return (client->fd);
}

int treat_client(int serverfd, int i, fd_set *active, ftp_t *ftp)
{
    int clientfd = -1;
    char *buffer;

    if (i == serverfd) {
        clientfd = accept_new_connection(serverfd, &ftp->client_head, ftp->pwd);
        if (clientfd < 0)
            return (84);
        FD_SET(clientfd, active);
    } else {
        buffer = read_from_client(i);
        if (buffer == NULL)
            return (84);
        handle_command(get_client_by_id(ftp->client_head, i), buffer,
                        active, ftp);
        printf("Received: %s\n", buffer);
        free(buffer);
    }
    return (0);
}

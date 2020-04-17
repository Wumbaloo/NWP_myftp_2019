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

int accept_new_connection(int serverfd, client_t **head, char *pwd)
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
    client->is_logged = 0;
    client->pwd = strdup(pwd);
    client->next = NULL;
    client_answer(client, 220, "Welcome client.");
    insert_new_node(head, client);
    printf("A new client joined with IP: %s.\n", inet_ntoa(client->data.sin_addr));
    return (client->fd);
}

char *remove_crlf(char *string, int valread)
{
    int new_valread = valread;
    char *new_string = NULL;

    if (string[valread - 1] == 10) {
        string[valread - 2] = '\0';
        new_valread--;
    }
    if (string[valread - 2] == 13) {
        string[valread - 3] = '\0';
        new_valread--;
    }
    if (new_valread != valread) {
        new_string = malloc(sizeof(char) * (new_valread + 1));
        if (!new_string)
            exit(84);
        memcpy(new_string, string, new_valread);
        new_string[new_valread] = '\0';
        free(string);
    }
    return ((new_string ? new_string : string));
}

char *read_from_client(int fd)
{
    int valread = -1;
    char buffer[1024];
    char *string = NULL;

    do {
        valread = read(fd, buffer, 1024);
    } while (valread <= 2 || (buffer[valread - 1] != 10
            && buffer[valread - 2] != 13));
    string = malloc(sizeof(char) * (valread + 1));
    if (string == NULL) {
        perror("malloc");
        exit(84);
    }
    memcpy(string, buffer, valread);
    string[valread] = '\0';
    string = remove_crlf(string, valread);
    return (string);
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
        handle_command(get_client_by_id(ftp->client_head, i), buffer, active, ftp);
        printf("Received: %s\n", buffer);
    }
    return (0);
}

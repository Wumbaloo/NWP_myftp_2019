/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client linked list
*/

#ifndef CLIENT_LIST_H_
#define CLIENT_LIST_H_

#include <arpa/inet.h>

typedef struct client_s {
    int fd;
    int data_socket;
    struct sockaddr_in config_socket;
    struct sockaddr_in data;
    struct client_s *next;
} client_t;

void insert_new_node(client_t **head, client_t *node);
void delete_node(client_t *head, client_t *node);
client_t *get_client_by_id(client_t *head, int id);

#endif
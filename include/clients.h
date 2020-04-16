/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Client linked list
*/

#ifndef CLIENTS_H_
#define CLIENTS_H_

#include "structs.h"

void insert_new_node(client_t **head, client_t *node);
void delete_node(client_t *head, client_t *node);
client_t *get_client_by_id(client_t *head, int id);
void free_list(client_t *head);

#endif
/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Clients linked list
*/

#include <stdlib.h>
#include "clients.h"

void insert_new_node(client_t **head, client_t *node)
{
    client_t *tmp = (*head);

    if (!(*head)) {
        *head = node;
        return;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
}

void delete_node(client_t *head, client_t *node)
{
    client_t *tmp = head;

    if (!head || !node)
        return;
    while (tmp->next) {
        if (tmp->next->fd == node->fd && tmp->next->next == node->next) {
            tmp->next = node->next;
            free(node);
            break;
        }
    }
}

client_t *get_client_by_id(client_t *head, int id)
{
    client_t *tmp = head;

    if (!head)
        return (NULL);
    while (tmp) {
        if (tmp->fd == id)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

void free_list(client_t *head)
{
    client_t *tmp = NULL;

    while (head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    if (tmp)
        free(tmp);
}

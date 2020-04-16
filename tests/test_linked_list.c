/*
** EPITECH PROJECT, 2019
** day 03
** File description:
** test_append
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "ftp.h"
#include "clients.h"

Test(insert_new_node, insert_when_empty)
{
    client_t *head = NULL;
    client_t *node = malloc(sizeof(client_t));

    if (!node)
        exit(84);
    node->fd = 2;
    node->next = NULL;
    insert_new_node(&head, node);
    cr_assert_eq(head->fd, 2);
    free_list(head);
}

Test(insert_new_node, basic_insert)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(client_t));
    if (!node)
        exit(84);
    head->fd = 1;
    head->next = NULL;
    node->fd = 2;
    node->next = NULL;
    insert_new_node(&head, node);
    cr_assert_eq(head->next->fd, 2);
    free_list(head);
}

Test(delete_node, delete_when_empty)
{
    client_t *head = NULL;

    delete_node(head, head);
    cr_assert_eq(head, NULL);
    free_list(head);
}

Test(delete_node, basic_delete)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(client_t));
    if (!node)
        exit(84);
    head->fd = 1;
    node->fd = 2;
    node->next = NULL;
    head->next = node;
    delete_node(head, node);
    cr_assert_eq(head->next, NULL);
    free_list(head);
}

Test(delete_node, advanced_delete)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node = malloc(sizeof(client_t));
    client_t *node1 = malloc(sizeof(client_t));

    if (!head || !node || !node1)
        exit(84);
    head->fd = 1;
    node->fd = 2;
    node1->fd = 3;
    head->next = node;
    node->next = node1;
    node1->next = NULL;
    delete_node(head, node);
    cr_assert_eq(head->next->fd, 3);
    free_list(head);
}

Test(delete_node, delete_inexistant)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(client_t));
    if (!node)
        exit(84);
    head->fd = 1;
    node->fd = 2;
    node->next = NULL;
    head->next = NULL;
    delete_node(head, node);
    cr_assert_eq(head->next, NULL);
    free_list(head);
    free_list(node);
}

Test(get_client, empty_getter)
{
    client_t *head = NULL;

    cr_assert_eq(get_client_by_id(head, 1), NULL);
}

Test(get_client, normal_getter)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(client_t));
    if (!node)
        exit(84);
    head->fd = 1;
    node->fd = 2;
    node->next = NULL;
    head->next = node;

    cr_assert_eq(get_client_by_id(head, 2), node);
    free_list(head);
}

Test(get_client, getter_inexistant)
{
    client_t *head = malloc(sizeof(client_t));
    client_t *node;

    if (!head)
        exit(84);
    node = malloc(sizeof(client_t));
    if (!node)
        exit(84);
    head->fd = 1;
    node->fd = 2;
    node->next = NULL;
    head->next = NULL;

    cr_assert_eq(get_client_by_id(head, 2), NULL);
    free_list(head);
    free_list(node);
}

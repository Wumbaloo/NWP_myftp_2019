/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Simple commands implementation
*/

#include "ftp.h"

void noop_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 200, "NOOP.");
}

void help_cmd(client_t *client, void *arg)
{
    (void) (arg);
    client_answer(client, 214, "This FTP works perfectly! I think so...");
}
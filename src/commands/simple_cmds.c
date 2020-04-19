/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Simple commands implementation
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "ftp.h"

void noop_cmd(client_t *client, void *arg, ftp_t *ftp)
{
    (void) (arg);
    (void) (ftp);
    client_answer(client, 200, "NOOP.");
}

void help_cmd(client_t *client, void *arg, ftp_t *ftp)
{
    (void) (arg);
    (void) (ftp);
    client_answer(client, 214, "This FTP works perfectly! I think so...");
}

void pwd_cmd(client_t *client, void *arg, ftp_t *ftp)
{
    (void) (arg);
    (void) (ftp);
    client_answer(client, 257, client->pwd);
}

void delete_file_cmd(client_t *client, void *input, ftp_t *ftp)
{
    char *command = strdup(input);
    char *txt = strtok(input, " ");
    FILE *file = NULL;

    (void) (ftp);
    if (txt)
        txt = strtok(NULL, " ");
    if (!txt)
        client_answer(client, 550, "Permission denied.");
    else {
        file = fopen(txt, "r");
        if (does_folder_exists(txt) || !file || remove(txt) != 0) {
            client_answer(client, 550,
                    "File unavailable (e.g., file not found, no access).");
            return;
        }
        client_answer(client, 250, "Requested file action okay, completed.");
        fclose(file);
    }
}
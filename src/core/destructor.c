/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Destructor
*/

#include <stdlib.h>
#include "ftp.h"

void free_ftp(ftp_t *ftp)
{
    for (int i = 0; ftp->cmds[i]; i++) {
        free(ftp->cmds[i]->command);
        free(ftp->cmds[i]);
    }
    free(ftp);
}
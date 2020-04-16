/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Commands handler
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "ftp.h"

void handle_command(client_t *client, char *input, fd_set *active, ftp_t *ftp)
{
    char *base_input = strdup(input);
    char *cmd = strtok(input, " ");

    if (!client)
        return;
    if (!cmd)
        cmd = input;
    for (int i = 0 ; ftp->cmds[i] ; i++) {
        if (strcmp(ftp->cmds[i]->command, cmd) == 0) {
            if (i == 0)
                ftp->cmds[i]->func(client, active);
            else
                ftp->cmds[i]->func(client, base_input);
            free(base_input);
            return;
        }
    }
    client_answer(client, 500, "What's next?");
    free(base_input);
}

command_t *create_command(char *name, void (*ptr)(client_t *, void *))
{
    command_t *cmd = malloc(sizeof(command_t));
    int len = strlen(name);

    if (cmd == NULL) {
        perror("command");
        exit(84);
    }
    cmd->command = malloc(sizeof(char) * (len + 1));
    if (cmd->command == NULL) {
        perror("command");
        exit(84);
    }
    strcpy(cmd->command, name);
    cmd->command[len] = '\0';
    cmd->func = ptr;
    return (cmd);
}

void initialize_commands(ftp_t *ftp)
{
    ftp->cmds = malloc(sizeof(command_t *) * 6);

    if (ftp->cmds == NULL) {
        perror("malloc");
        exit(84);
    }
    ftp->cmds[0] = create_command("EXIT", &close_connection);
    ftp->cmds[1] = create_command("USER", &set_username);
    ftp->cmds[2] = create_command("PASS", &set_password);
    ftp->cmds[3] = create_command("PASV", &pasv_command);
    ftp->cmds[4] = create_command("NOOP", &noop_cmd);
    ftp->cmds[5] = NULL;
}
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

void execute_command(client_t *client, command_t **cmds, int i, void *arg)
{
    if (i == 0) {
        cmds[i]->func(client, (fd_set *) arg);
    } else if (cmds[i]->need_login != client->is_logged)
        client_answer(client, 530, "Not logged in.");
    else {
        cmds[i]->func(client, (char *) arg);
        free(arg);
    }
}

void handle_command(client_t *client, char *input, fd_set *active, ftp_t *ftp)
{
    char *base = strdup(input);
    char *cmd = strtok(input, " ");
    void *arg = NULL;

    if (!client)
        return;
    if (!cmd)
        cmd = input;
    for (int i = 0 ; ftp->cmds[i] ; i++) {
        if (strcmp(ftp->cmds[i]->command, cmd) == 0) {
            arg = (i == 0 ? (void *) active : (void *) base);
            execute_command(client, ftp->cmds, i, arg);
            return;
        }
    }
    client_answer(client, 500, "What's next?");
    free(base);
}

command_t *create_command(char *txt, int login, void (*ptr)(client_t *, void *))
{
    command_t *cmd = malloc(sizeof(command_t));
    int len = strlen(txt);

    if (cmd == NULL) {
        perror("command");
        exit(84);
    }
    cmd->command = malloc(sizeof(char) * (len + 1));
    if (cmd->command == NULL) {
        perror("command");
        exit(84);
    }
    strcpy(cmd->command, txt);
    cmd->command[len] = '\0';
    cmd->func = ptr;
    cmd->need_login = login;
    return (cmd);
}

void initialize_commands(ftp_t *ftp)
{
    ftp->cmds = malloc(sizeof(command_t *) * 7);

    if (ftp->cmds == NULL) {
        perror("malloc");
        exit(84);
    }
    ftp->cmds[0] = create_command("EXIT", 0, &close_connection);
    ftp->cmds[1] = create_command("USER", 0, &set_username);
    ftp->cmds[2] = create_command("PASS", -1, &set_password);
    ftp->cmds[3] = create_command("PASV", 1, &pasv_command);
    ftp->cmds[4] = create_command("NOOP", 1, &noop_cmd);
    ftp->cmds[5] = create_command("HELP", 0, &help_cmd);
    ftp->cmds[6] = NULL;
}
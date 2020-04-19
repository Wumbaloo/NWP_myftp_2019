/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Commands handler
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "commands.h"
#include "ftp.h"

void execute_command(client_t *client, ftp_t *ftp, int i, void *arg)
{
    if (i == 0) {
        ftp->cmds[i]->func(client, (fd_set *) arg, ftp);
    } else if (ftp->cmds[i]->need_login > client->is_logged)
        client_answer(client, 530, "Not logged in.");
    else {
        ftp->cmds[i]->func(client, (char *) arg, ftp);
        free(arg);
    }
    if ((strcmp(ftp->cmds[i]->command, "USER") != 0 &&
        strcmp(ftp->cmds[i]->command, "PASS") != 0) && client->is_logged == -1)
        client->is_logged = 0;
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
            execute_command(client, ftp, i, arg);
            return;
        }
    }
    client_answer(client, 500, "What's next?");
    free(base);
}

command_t *create_command(char *txt, int login,
                            void (*ptr)(client_t *, void *, ftp_t *))
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

void list_cmd(client_t *client, void *arg, ftp_t *ftp)
{
    (void) (arg);
    (void) (ftp);
    if (client->data_socket == -1 || client->data_fd == -1) {
        client_answer(client, 425, "Use PORT or PASV first.");
        return;
    }
    client_answer(client, 150, "Here comes the directory listing.");
    dprintf(client->data_fd, "LIST\r\n");
    dprintf(client->data_fd, "TODO: LS\r\n");
    client_answer(client, 226, "Directory send OK.");
}

void initialize_commands(ftp_t *ftp)
{
    ftp->cmds = malloc(sizeof(command_t *) * 11);

    if (ftp->cmds == NULL) {
        perror("malloc");
        exit(84);
    }
    ftp->cmds[0] = create_command("QUIT", 0, &close_connection);
    ftp->cmds[1] = create_command("USER", -2, &set_username);
    ftp->cmds[2] = create_command("PASS", -2, &set_password);
    ftp->cmds[3] = create_command("PASV", 1, &pasv_command);
    ftp->cmds[4] = create_command("NOOP", 1, &noop_cmd);
    ftp->cmds[5] = create_command("HELP", 1, &help_cmd);
    ftp->cmds[6] = create_command("CWD", 1, &cwd_cmd);
    ftp->cmds[7] = create_command("PWD", 1, &pwd_cmd);
    ftp->cmds[8] = create_command("DELE", 1, &delete_file_cmd);
    ftp->cmds[9] = create_command("LIST", 1, &list_cmd);
    ftp->cmds[10] = NULL;
}
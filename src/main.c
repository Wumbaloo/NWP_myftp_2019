/*
** EPITECH PROJECT, 2019
** My FTP
** File description:
** Main file
*/

#include "ftp.h"

int main(int ac, char **av)
{
    int result = launch_server(ac, av);

    return (result);
}
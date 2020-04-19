/*
** EPITECH PROJECT, 2019
** day 03
** File description:
** test_append
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ftp.h"
#include "clients.h"

char *get_folder(char *input);

Test(get_folder, basic_test)
{
    char *target = "bin";
    char *folder;

    if (chdir("/usr") != 0)
        cr_assert(0 != 1);
    folder = get_folder(target);
    cr_assert_str_eq(folder, "/usr/bin");
}

Test(get_folder, full_path_test)
{
    char *target = "/etc/";
    char *folder = get_folder(target);

    cr_assert_str_eq(folder, "/etc");
}

Test(get_folder, relative_path_test)
{
    char *target = "../";
    char *folder;

    if (chdir("/usr") != 0)
        cr_assert(0 != 1);
    folder = get_folder(target);
    cr_assert_str_eq(folder, "/");
}

Test(get_folder, relative_path_test_2)
{
    char *target = "NWP_myftp_2019";
    char *folder;

    if (chdir("/home/william") != 0)
        cr_assert(0 != 1);
    folder = get_folder(target);
    cr_assert_str_eq(folder, "/home/william/NWP_myftp_2019");
}

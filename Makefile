##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Just a Makefile that compiles everything
##

SRC_DIR	=	src/

FILES	=	client_handler.c	\
			client_list.c		\
			commands.c			\
			core.c				\
			initialization.c	\
			useful.c			\

MAIN_FILE	=	main.c

SRC			=	$(addprefix $(SRC_DIR), $(FILES))
SRC_MAIN	=	$(addprefix $(SRC_DIR), $(MAIN_FILE))

OBJ		=	$(SRC:.c=.o)
OBJ_MAIN=	$(SRC_MAIN:.c=.o)

CFLAGS	=	-I include

NAME	=	myftp

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_MAIN)

debug:
	$(CC) -o $(NAME) $(SRC) $(SRC_MAIN) $(CFLAGS) -Wall -Werror -Wextra -g

tests_run:
	make -C tests tests_run from="$(CURDIR)" files="$(SRC)"

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJ) $(OBJ_MAIN)

re: fclean all
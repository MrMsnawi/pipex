SRC = 	main.c \
		utils/ft_putstr_fd.c utils/ft_split.c utils/code.c utils/ft_strncmp.c \
		utils/ft_strlen.c utils/ft_strjoin.c utils/ft_strdup.c utils/utils.c

OBJ = $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = pipex

HEADS = pipex.h

all: $(NAME)

%.o: %.c $(HEADS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
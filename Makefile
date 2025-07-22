# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 13:39:56 by taewonki          #+#    #+#              #
#    Updated: 2025/07/16 18:02:12 by taewonki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -I$(LIBFT_DIR)

SRC_DIR = srcs
LIBFT_DIR = Libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a

NAME = minishell

SRC = $(SRC_DIR)/execute_cmds.c $(SRC_DIR)/execute_cmds_utils.c \
	$(SRC_DIR)/free_utils.c $(SRC_DIR)/lexing.c $(SRC_DIR)/list_func.c \
	$(SRC_DIR)/minishell.c $(SRC_DIR)/parse_utils.c $(SRC_DIR)/pipe_utils.c \
	$(SRC_DIR)/process_utils.c $(SRC_DIR)/redirect.c

# SRC_MAIN = $(SRC_DIR)/push_swap.c

OBJ = $(SRC:.c=.o)
# MAIN_OBJ = $(SRC_MAIN:.c=.o)

all: $(NAME)

$(NAME): $(FT_LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FT_LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(MAIN_OBJ): $(SRC_DIR)/push_swap.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all bonus

.PHONY: all clean fclean re bonus

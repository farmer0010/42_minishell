# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 13:39:56 by taewonki          #+#    #+#              #
#    Updated: 2025/08/07 12:05:51 by taewonki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -f

SRCS_DIR		=	srcs
OBJS_DIR		=	objs
INCLUDES_DIR	=	includes
LIBFT_DIR		=	Libft
LIBFT_A			=	$(LIBFT_DIR)/libft.a

SRCS			=	srcs/builtin.c \
					srcs/builtin_cd.c \
					srcs/builtin_echo_pwd.c \
					srcs/builtin_env.c \
					srcs/builtin_exit.c \
					srcs/builtin_export.c \
					srcs/builtin_handler.c \
					srcs/builtin_single.c \
					srcs/builtin_unset.c \
					srcs/builtin_validation.c \
					srcs/cmd_list_func.c \
					srcs/env_convert.c \
					srcs/env_expansion.c \
					srcs/env_getters.c \
					srcs/env_init.c \
					srcs/env_set_unset.c \
					srcs/env_utils.c \
					srcs/execute_cmds.c \
					srcs/execute_cmds_utils.c \
					srcs/exec_utils.c \
					srcs/free_cmd_utils.c \
					srcs/free_utils.c \
					srcs/here_doc.c \
					srcs/init_data.c \
					srcs/lexing.c \
					srcs/lexing_handler.c \
					srcs/lex_util.c \
					srcs/libft_plus_utils.c \
					srcs/libft_plus_utils2.c \
					srcs/list_func.c \
					srcs/loop.c \
					srcs/loop_utils.c \
					srcs/minishell.c \
					srcs/multi_cmd_handler.c \
					srcs/parse_free_util.c \
					srcs/parse_util.c \
					srcs/parsing.c \
					srcs/pipe_utils.c \
					srcs/process_child.c \
					srcs/process_manager.c \
					srcs/redirect.c \
					srcs/signal.c \
					srcs/signal_utils.c \
					srcs/lex_handler_util.c

OBJS			=	$(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

INCLUDES		=	-I$(INCLUDES_DIR) -I$(LIBFT_DIR)
LDFLAGS			=	-lreadline
LDLIBS			=	-L$(LIBFT_DIR) -lft

all:			$(NAME)

$(NAME):		$(OBJS_DIR) $(OBJS) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
				@make -s -C $(LIBFT_DIR) bonus

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
				@make -s -C $(LIBFT_DIR) clean
				@$(RM) -r $(OBJS_DIR)

fclean:			clean
				@make -s -C $(LIBFT_DIR) fclean
				@$(RM) $(NAME)

re:				fclean all

.PHONY: all clean fclean re

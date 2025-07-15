/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:33 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/11 01:50:44 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_cmd {
    char **argv;
    int infile;
    int outfile;
    int is_builtin;
    struct s_cmd *next;
} t_cmd;

typedef enum e_state {
    s_in_general,
    // 일반적인 상태
    s_in_double_quote,
    // 더블 쿼트 안에 있는 상태
    s_in_operation,
    // 연산자 안에 있는 상태
    s_in_single_quote,
    // 싱글 쿼트 안에 있는 상태
    s_in_word
    // 단어 안에 있는 상태
} t_state;

typedef enum e_token_type {
    WORD,
    // 일반 단어, 명령어도 여기 포함
    OPERATOR,
    PIPE,
    REDIRECT_IN,
    HERE_DOC,
    REDIRECT_OUT,
    REDIRECT_APPEND
} t_token_type;

typedef struct s_token {
    char *value;
    t_token_type type;
} t_token;
// 여기서 lexing이 완료되어서 토큰화 되어서 이 구조체에 저장된 정보는
// 원자적인 최소단위 정보이다.

typedef struct s_node {
    t_token *token;
    struct s_node *prev;
    struct s_node *next;
} t_node;

// lexing.c
void    lexing(const char *cmd);

void    execute_cmds(t_cmd *cmd);
char    *find_executable(char *cmd_name, char **envp);
char    *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int		handle_redirects(t_cmd *cmd);
void    free_argv(char **argv);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/21 18:49:34 by taewonki         ###   ########.fr       */
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
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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
    // 일반적인 상태, 따옴표, 특수 연산자 바깥에 있는 상태
    s_in_double_quote,
    // 더블 쿼트 안에 있는 상태, / $ 등의 문자는 처리되어야 한다.
    s_in_single_quote,
    // 싱글 쿼트 안에 있는 상태, 내부의 모든 문자는 리터럴로 처리되어야 한다.
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

typedef enum e_quote_type {
    not_q,
    s_q,
    d_q
}   t_quote_type;

typedef struct s_token {
    char *value;
    t_token_type type;
    t_quote_type quote_status;
} t_token;
// 여기서 lexing이 완료되어서 토큰화 되어서 이 구조체에 저장된 정보는
// 원자적인 최소단위 정보이다.

typedef struct s_node {
    t_token *token;
    struct s_node *prev;
    struct s_node *next;
} t_node;

// lexing.c


void    execute_cmds(t_cmd *cmd);
char    *find_executable(char *cmd_name, char **envp);
char    *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int		handle_redirects(t_cmd *cmd);
int		ft_strcmp(const char *s1, const char *s2);
void    free_argv(char **argv);

// parse_utils.c
int		ft_isquote(char c);
int		ft_isspace(char c);
char	handle_escape(char c);
int		ft_isoper(char c);
int		ft_isspace(char c);

// list_func.c
t_node	*create_node(int type, t_quote_type q, char *value);
void	append_token(t_node **head, t_node *node);

#endif

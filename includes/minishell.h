/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:33 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/10 16:33:27 by taewonki         ###   ########.fr       */
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

typedef struct s_statemachine
{
    int s_in_general;
    int s_in_word;
    int s_in_single_quote;
    int s_in_double_quote;
    int s_in_operation;
}   t_statemachine;

typedef enum e_token_type
{
    token_word,
    // 일반적인 단어 ls, cat, $HOME 등의 "따옴표 안의 내용"
    token_pipe,
    // 파이프 ( | )
    token_redirect_out,
    // 출력 리다이렉션 ( > )
    token_append_redirect,
    // 추가 출력 리다이렉션 ( >> )
    token_redirect_in,
    // 입력 리다이렉션 ( < )
    token_redirect_here_doc
    // 히어독 ( << )
}   t_token_type;

typedef struct  s_token
{
    int token_type;
    // 토큰 종류
    char    *value;
    // 토큰의 실제 문자열 값
}   t_token;

void    execute_cmds(t_cmd *cmd);
char    *find_executable(char *cmd_name, char **envp);
char    *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
void    free_argv(char **argv);

//parse_util.c
int	ft_isspace(char c);

//lexing.c
int lexing(char *cmd);

#endif

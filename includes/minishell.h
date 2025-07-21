/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:13:30 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/16 14:13:30 by taewonki         ###   ########.fr       */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

extern int	g_exit_status;

/*
** t_env: 환경 변수의 key-value 쌍
*/
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/*
** t_cmd: 파싱된 명령어 정보를 담는 구조체
*/
typedef struct s_cmd
{
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

/*
** t_state: 렉서가 문자열을 토큰화할 때의 상태
*/
typedef enum e_state
{
	s_in_general,
	s_in_double_quote,
	s_in_single_quote,
	s_in_word
}	t_state;

/*
** t_token_type: 토큰의 종류
*/
typedef enum e_token_type
{
	WORD,
	OPERATOR,
	PIPE,
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	REDIRECT_APPEND
}	t_token_type;

/*
** t_token: 렉싱 결과 생성된 개별 토큰
*/
typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

/*
** t_node: 토큰 리스트 노드
*/
typedef struct s_node
{
	t_token			*token;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

/*
** t_pipe_data: 파이프 실행 관련 데이터
*/
typedef struct s_pipe_data
{
	int		idx;
	int		count;
	int		**pipefd;
}	t_pipe_data;

/*
** t_shell_data: 쉘의 전체 상태 정보
*/
typedef struct s_shell_data
{
	t_list			*env_list;
	t_cmd			*cmd_list;
	t_node			*token_list;
	t_pipe_data		pipe_data;
	int				stdin_backup;
	int				stdout_backup;
}	t_shell_data;

/* execute_cmds.c */
void		execute_cmds(t_shell_data *data);

/* execute_cmds_utils.c */
char		*find_executable(char *cmd_name, t_list *env_list);
char		*ft_strjoin_three(const char *s1, const char *s2, const char *s3);

/* redirect.c */
int			handle_redirects(t_cmd *cmd);

/* libft_plus_utils.c */
int			ft_strcmp(const char *s1, const char *s2);
int			is_numeric(const char *str);

/* free_utils.c */
void		free_argv(char **argv);
void		free_all(t_shell_data *data);
void		free_cmd_list(t_cmd *cmd_list);
void		free_token_list(t_node *token_list);
void		free_env_node(void *content);

/* signal_utils.c */
void		sigint_handler(int signo);
void		sigquit_handler(int signo);

/* signal.c */
void		init_signal(void);

/* builtin.c */
int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_shell_data *data);

/* builtin_utils.c */
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_list *env_list);
int			builtin_pwd(void);
int			builtin_env(t_list *env_list);
int			builtin_exit(char **argv, t_shell_data *data);

/* builtin_utils2.c (export) */
int			builtin_export(char **argv, t_list **env_list);
int			is_valid_identifier(const char *str);

/* builtin_utils3.c (unset) */
int			builtin_unset(char **argv, t_list **env_list);

/* env_manage.c */
t_list		*init_env_list(char **envp_sys);
char		*get_env_value(t_list *env_list, const char *key);
int			set_env_value(t_list **env_list, const char *key, const char *value);
int			unset_env_value(t_list **env_list, const char *key);
char		**convert_env_list_to_array(t_list *env_list);
void		free_env_array(char **env_array);

/* pipe_utils.c */
int			**create_pipes(int count);
void		setup_pipes(int idx, int count, int **pipefd);
void		close_unused_pipes(int **pipefd, int count);

/* process_utils.c */
void		child_process(t_cmd *cmd, t_shell_data *data);
void		run_child_processes(t_cmd *cmd, t_shell_data *data);

/* loop.c */
void		start_minishell(t_shell_data *data);

/* make_fake_cmd.c */
t_cmd		*make_fake_cmd(void);

/* parse_utils.c */
int			ft_isquote(char c);
int			ft_isspace(char c);
char		handle_escape(char c);
int			ft_isoper(char c);

/* list_func.c */
t_node		*create_node(int type, char *value);
void		append_token(t_node **head, t_node *node);

#endif

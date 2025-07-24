/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/24 14:42:48 by taewonki         ###   ########.fr       */
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
# ifndef ERR
#  define ERR -1
# endif

extern int	g_exit_status;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_cmd
{
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_state
{
	s_in_general,
	s_in_double_quote,
	s_in_single_quote,
	s_in_word
}	t_state;

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	REDIRECT_APPEND
}	t_token_type;

typedef enum e_quote_type {
	not_q,
	s_q,
	d_q
}	t_quote_type;

typedef struct s_token {
	t_token_type	type;
	t_quote_type	quote_status;
	char 			*val;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_pipe_data
{
	int		idx;
	int		count;
	int		**pipefd;
}	t_pipe_data;

typedef struct s_shell_data
{
	t_list		*env_list;
	t_cmd		*cmd_list;
	t_token		*token_list;
	t_pipe_data	pipe_data;
	int			stdin_backup;
	int			stdout_backup;
}	t_shell_data;

/* loop.c */
void		start_minishell(t_shell_data *data);

/* execute_cmds.c */
void		execute_cmds(t_shell_data *data);
void		handle_multiple_cmds(t_shell_data *data, t_cmd *cmd_list);

/* execute_cmds_utils.c */
char		*find_executable(char *cmd_name, t_list *env_list);
char		*ft_strjoin_three(const char *s1, const char *s2, const char *s3);

/* redirect.c */
int			handle_redirects(t_cmd *cmd);

/* libft_plus_utils.c */
int			ft_strcmp(const char *s1, const char *s2);
int			is_numeric(const char *str);
long long	ft_atoll(const char *str);
char		*ft_strjoin_free(char *s1, char *s2);

/* free_utils.c */
void		free_argv(char **argv);
void		free_cmd_list(t_cmd *cmd_list);
void		free_token_list(t_token *token_list);
void		free_env_node(void *content);
void		free_pipes(int **pipefd, int count);
void		free_env_array(char **env_array);
void		free_all(t_shell_data *data);

/* signal.c */
void		init_signal(void);
void		sigint_handler(int signo);
void		sigquit_handler(int signo);

/* builtin.c */
int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_shell_data *data);

/* builtin_cd.c */
int			builtin_cd(char **argv, t_shell_data *data);

/* builtin_echo_pwd.c */
int			builtin_echo(char **argv);
int			builtin_pwd(void);

/* builtin_env.c */
int			builtin_env(t_list *env_list);

/* builtin_exit.c */
int			builtin_exit(char **argv, t_shell_data *data);

/* builtin_export.c */
int			builtin_export(char **argv, t_list **env_list);
void		handle_export_arg(const char *arg, t_list **env_list);
void		handle_export_with_value(t_list **env_list,
				const char *arg, char *equal_sign);
void		handle_export_no_value(t_list **env_list, const char *arg);

/* builtin_validation.c */
int			is_valid_identifier(const char *str);
void		handle_export_key_value(t_list **env_list,
				char *key, char *value);

/* builtin_handler.c */
void		handle_single_builtin(t_cmd *cmd, t_shell_data *data);

/* builtin_single.c */
int			is_single_builtin(t_cmd *cmd);

/* builtin_unset.c */
int			builtin_unset(char **argv, t_list **env_list);

/* env_init.c */
t_list		*init_env_list(char **envp_sys);

/* env_getters.c */
char		*get_env_value(t_list *env_list, const char *key);

/* env_set_unset.c */
int			set_env_value(t_list **env_list,
				const char *key, const char *value);
int			unset_env_value(t_list **env_list, const char *key);

/* env_convert.c */
char		**convert_env_list_to_array(t_list *env_list);

/* env_utils.c */
t_env		*create_env_node_content(const char *key, const char *value);

/* pipe_utils.c */
int			**create_pipes(int count);
void		setup_pipes(int idx, int count, int **pipefd);
void		close_unused_pipes(int **pipefd, int count);
void		close_all_pipe_fds_in_child(int **pipefd, int count);

/* process_child.c */
void		child_process(t_cmd *cmd, t_shell_data *data);

/* process_manager.c */
void		run_child_processes(t_cmd *cmd_list, t_shell_data *data);

/* make_fake_cmd.c */
t_cmd		*make_fake_cmd(void);

/* parse_utils.c */
int			ft_isquote(char c);
int			ft_isspace(char c);
int			ft_isoper(char c);

/* parse_free_util.c */
void		ft_free_lst(t_token **head);

/* list_func.c */
t_token		*create_token(int type, t_quote_type q, char *val);
int			append_token(t_token **head, t_token *token);



#endif

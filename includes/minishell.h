/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/30 13:00:05 by taewonki         ###   ########.fr       */
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
	char			*filepath;
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

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	REDIRECT_APPEND
}	t_token_type;

typedef enum e_quote_type
{
	not_q,
	s_q,
	d_q
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	t_quote_type	quote_status;
	char			*val;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_pipe_data
{
	int	idx;
	int	count;
	int	**pipefd;
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

/* init_data.c */
int			init_shell_data(t_shell_data *data, char **envp);
void		print_init_error(void);

/* loop.c */
void		start_minishell(t_shell_data *data);

/* loop_utils.c */
char		*read_user_input(void);
int			perform_lexing(t_shell_data *data, char *input);
int			perform_parsing(t_shell_data *data);
void		cleanup_cmd_data(t_shell_data *data);

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
char		*ft_strjoin_free(char *s1, char *s2);
long long	ft_atoll(const char *str);
int			ft_isspace(char c);

/* free_utils.c */
void		free_argv(char **argv);
void		free_cmd_list(t_cmd *cmd_list);
void		free_token_list(t_token *token_list);
void		free_cmd_node(t_cmd *node);
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
void		handle_export_key_value(t_list **env_list, char *key, char *value);

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
void		free_env_content(void *content);

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

/* cmd_list_func.c */
t_cmd		*create_cmd_node(t_token *start, t_token *end, t_shell_data *data);
t_cmd		*get_cmd_list(t_token **head, t_shell_data *data);
int			append_cmd(t_cmd **head, t_cmd *cmd);
int			create_append_cmd(t_cmd **head,
				t_token *start, t_token *end, t_shell_data *data);
t_cmd		*create_init_cmd(t_token *start, t_token *end);

/* env_expansion.c */
char		*expand_str(const char *val, t_shell_data *data);
char		*end_expansion(char *expanded, char *cur);
char		*append_pre_doller(char *expanded,
				const char *pos, const char *cur);
char		*process_expansion(const char *cur,
				char *expanded, int *env_len, t_shell_data *data);

/* lex_utils.c */
int			ft_isquote(char c);
int			ft_isoper(char c);
int			is_redirect(t_token_type type);

/* lexing_handler.c */
int			handle_general(const char *cmd, int *i,
				t_state *s, t_token **head);
int			handle_in_oper(const char *cmd, int *i,
				t_token **head);
int			handle_s_quote(const char *cmd, int *i,
				t_state *s, t_token **head);
int			handle_d_quote(const char *cmd, int *i,
				t_state *s, t_token **head);
int			handle_in_word(const char *cmd, int *i,
				t_state *s, t_token **head);

/* lexing.c */
void		get_token_info(const char *cmd, t_token **head);

/* list_func.c */
t_token		*create_token(int type, t_quote_type q, char *val);
int			append_token(t_token **head, t_token *token);
t_token		*last_token(t_token *head);
t_cmd		*get_last_cmd(t_cmd *head);

/* parse_free_util.c */
void		ft_free_lst(t_token **head);
void		invalid_fd(int infile_fd, int outfile_fd);

/* parse_util.c */
int			valid_syntax(t_token **head);
int			get_argv_set_fd(t_cmd *cmd, t_token *start,
				t_token *end, int *argv_len);
int			set_argv_val(t_cmd *cmd, t_token *cur, int idx, \
	t_shell_data *data);
int			set_fd(t_token *cur, t_cmd *cmd);

/* parsing.c */
void		syntax_error(const char *token_value);
char		*get_env_name_len(const char *val, int *env_len);
t_cmd		*get_cmd_info(t_token **head, t_shell_data *data);

//here_doc.c
int			here_doc(char *end, char **filepath);

//debug_parse.c
void	print_token_lst(t_token *head);
void	print_cmd_lst(t_cmd *head);

#endif

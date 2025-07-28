/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:48:02 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/24 15:45:03 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash
// bash의 구문 오류 종료 코드는 2
int	is_redirect(t_token_type type);
void	parse_input(t_token **head);
static void syntax_error(const char *token_value);
int	valid_syntax(t_token **head);
int	get_argv_set_fd(t_cmd *cmd, t_token *start, int *argv_len);
char	*get_env_name_len(char *val, int *env_len);
char	*expand_str(char *val);
t_cmd	*create_cmd_node(t_token *start);
t_cmd	*get_cmd_block(t_token **head);
int	here_doc(char *end);

int	is_redirect(t_token_type type)
{
	if (type == REDIRECT_IN)
		return (1);
	else if (type == HERE_DOC)
		return (1);
	else if (type == REDIRECT_OUT)
		return (1);
	else if (type == REDIRECT_APPEND)
		return (1);
	else
		return (0);
}

static void syntax_error(const char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
}

void	parse_input(t_token **head)
{
	if (valid_syntax(head) != 0)
		return (ft_free_lst(head), 1);

}

int	valid_syntax(t_token **head)
{
	t_token	*cur;

	if (!head || !*head)
		return (0);
	cur = *head;
	if (cur->type == PIPE)
		return (syntax_error(cur->val), 2);
	while (cur)
	{
		if (cur->next != NULL)
		{
			if (cur->type == PIPE && cur->next->type == PIPE)
				return (syntax_error(cur->next->val), 2);
			else if (is_redirect(cur->type) &&\
						cur->next->type != WORD)
				return (syntax_error(cur->next->val), 2);
		}
		else
		{
			if (is_redirect(cur->type) || cur->type == PIPE)
				return (syntax_error("newline"), 2);
		}
		cur = cur->next;
	}
	return (0);
}

int	get_argv_set_fd(t_cmd *cmd, t_token *start, int *argv_len)
{
	t_token	*cur;

	cur = start;
	while (cur && cur->type != PIPE)
	{
		if (is_redirect(cur->type))
		{
			if (cur->type == REDIRECT_IN)
				cmd->infile = open(cur->next->val, O_RDONLY);
			else if (cur->type == HERE_DOC)
				cmd->infile = here_doc(cur->next->val);
			else if (cur->type == REDIRECT_OUT)
				cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (cur->type == REDIRECT_APPEND)
				cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
			cur = cur->next->next;
			if (cmd->infile < 0 || cmd->outfile < 0)
			{
				if (cmd->infile > 0)
					close(cmd->infile);
				if (cmd->outfile > 0)
					close(cmd->outfile);
				return (ft_putstr_fd("open()fail\n", 2), ERR);
			}
			continue ;
		}
		if (cur->type == WORD)
			(*argv_len)++;
		cur = cur->next;
	}
	return (1);
}

char	*get_env_name_len(char *val, int *env_len)
{
	char	*env_name;
	int		i;

	if (!val || !*val)
		return (NULL);
	if (val[0] == '$')
		return (*env_len = 1, ft_strdup("$"));
	else if (val[0] == '?')
		return (*env_len = 1, ft_strdup("?"));
	i = 0;
	while (val[i] && (ft_isalnum(val[i]) || val[i] == '_'))
		i++;
	env_name = ft_substr(val, 0, i);
	if (!env_name)
		return (NULL);
	*env_len = i;
	return (env_name);
}

char	*expand_str(char *val)
{
	char	*expanded;
	char	*cur_remain[2];
	char	*doller_pos;
	char	*env[2];
	// 0 = env_name, 1 = env_value
	int		env_len;

	if (!val)
		return (NULL);
	cur_remain[0] = val;
	expanded = ft_strdup("");
	while (*cur_remain[0])
	{
		doller_pos = ft_strchr(cur_remain[0], '$');
		if (!doller_pos)
		{
			cur_remain[1] = ft_strdup(cur_remain[0]);
			if (!cur_remain[1])
				return (free(expanded), NULL);
			expanded = ft_strjoin_free(expanded,cur_remain[1]);
			if (!expanded)
				return (NULL);
			break ;
		}
		if (doller_pos > cur_remain[0])
		{
			cur_remain[1] = ft_substr(cur_remain[0], 0, doller_pos - cur_remain[0]);
			if (!cur_remain[1])
				return (free(expanded), NULL);
			expanded = ft_strjoin_free(expanded, cur_remain[1]);
			if (!expanded)
				return (NULL);
		}
		cur_remain[0] = doller_pos + 1;
		env[0] = get_env_name_len(cur_remain[0], &env_len);
		if (!env[0])
			return (free(expanded), NULL);
		if (env[0][0] == '$')
			env[1] = ft_itoa(getpid());
		else if (env[0][0] == '?')
			env[1] = ft_itoa(g_exit_status);
		else
			env[1] = ft_strdup(getenv(env[0]));
		free(env[0]);
		if (env[1])
		{
			expanded = ft_strjoin_free(expanded, env[1]);
			if (!expanded)
				return (free(env[1]), NULL);
		}
		else
		{
			expanded = ft_strjoin_free(expanded, "");
			if (!expanded)
				return (NULL);
		}
		cur_remain[0] += env_len;
	}
	return (expanded);
}

t_cmd	*create_cmd_node(t_token *start)
{
	t_cmd	*cmd;
	t_token	*cur;
	int		argv_len;
	int		i;

	if (!start)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	if (get_argv_len(cmd, start, &argv_len) < 0)
		return (NULL);
	cur = start;
	cmd->argv = malloc(sizeof(char *) * (argv_len + 1));
	if (!argv_len)
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		return (free(cmd), NULL);
	}
	i = 0;
	cur = start;
	while (cur && i < argv_len)
	{
		if (cur->type == PIPE)
			break ;
		if (is_redirect(cur->type))
		{
			cur = cur->next->next;
			continue ;
		}
		if (start->quote_status == s_q)
			cmd->argv[i] = ft_strdup(cur->val);
		else
			cmd->argv[i] = expand_str(cur->val);
		i++;
		cur = cur->next;
	}
	cmd->argv[argv_len] = NULL;
	return (cmd);
}

t_cmd	*get_cmd_block(t_token **head)
{
	t_token	*node[2];
	// 0 = cur, 1 = start
	t_cmd	*new_cmd[2];
	// 0 = cmd_head; 1 = cmd_node;

	if (!head || !*head)
		return (NULL);
	node[0] = head;
	node[1] = head;
	new_cmd[0] = NULL;
	while (node[0])
	{
		if (node[0]->type == PIPE)
		{
			new_cmd[1] = create_cmd_node(node[1]);
			if (!new_cmd[1])
				return (ft_putstr_fd("create_cmd() fail\n", 2), NULL);
			node[1] = node[0]->next;
		}
		node[0] = node[0]->next;
	}
	return (new_cmd[0]);
}

int	here_doc(char *end)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("open() fail\n", 2), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (fd);
}

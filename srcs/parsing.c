/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:48:02 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/22 16:08:36 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash
// bash의 구문 오류 종료 코드는 2

int		is_redirect(t_token_type type);
void	parse_input(t_token **head);
int		valid_syntax(t_token **head);
t_cmd	*create_cmd_node(t_token *start);
t_cmd	*get_cmd_block(t_token **head);

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
		return (syntax_error(cur->value), 2);
	while (cur)
	{
		if (cur->next != NULL)
		{
			if (cur->type == PIPE && cur->next->type == PIPE)
				return (syntax_error(cur->next->value), 2);
			else if (is_redirect(cur->type) &&\
						cur->next->type != WORD)
				return (syntax_error(cur->next->value), 2);
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
				cmd->infile = open(cur->next->value, O_RDONLY);
			else if (cur->type == HERE_DOC)
				cmd->infile = here_doc()
				//보류
				// here_doc 함수 만들어야 함
			else if (cur->type == REDIRECT_OUT)
				cmd->outfile = open(cur->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (cur->type == REDIRECT_APPEND)
				cmd->outfile = open(cur->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
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

char	*expand_str(char *val, t_quote_type q)
{
	char	*expanded;

	if (q == s_q)
	{
		expanded = ft_strdup(val);
		if (expanded == NULL)
			return (ft_putstr_fd("malloc failed\n", 2), NULL);
		return (expanded);
	}
	else if (q == d_q || q == not_q)
	{
		expanded = get_expanded_str();

	}
}

t_cmd	*create_cmd_node(t_token *start)
{
	t_cmd	*cmd;
	t_token	cur;
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
	while (cur)
	{
		if (cur->type == PIPE)
			break ;
		if (is_redirect(cur->type))
		{
			cur = cur->next->next;
			continue ;
		}
		if (start->quote_status == not_q)
		{

		}
		else if (start->quote_status == s_q)
		{

		}
		else if (start->quote_status == d_q)
		{

		}
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
		if (cur->type == PIPE)
		{
			new_cmd[1] = create_cmd_node(node[1]);
			if (!new_cmd[1])
				return (ft_putstr_fd("create_cmd() fail\n"), NULL);
			node[1] = node[0]->next;
		}
		node[0] = node[0]->next;
	}
	return (new_cmd[0]);
}


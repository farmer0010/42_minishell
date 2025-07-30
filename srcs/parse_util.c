/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:37:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/30 11:53:37 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		valid_syntax(t_token **head);
int		get_argv_set_fd(t_cmd *cmd, t_token *start, t_token *end, \
	int *argv_len);
int		set_argv_val(t_cmd *cmd, t_token *cur, int idx, t_shell_data *data);
int		set_fd(t_token *cur, t_cmd *cmd);

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
			else if (is_redirect(cur->type) && \
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

int	get_argv_set_fd(t_cmd *cmd, t_token *start, t_token *end, int *argv_len)
{
	t_token	*cur;

	cur = start;
	while (cur && cur != end->next)
	{
		if (is_redirect(cur->type))
		{
			if (set_fd(cur, cmd) < 0)
				return (invalid_fd(cmd->infile, cmd->outfile), ERR);
			cur = cur->next->next;
			continue ;
		}
		if (cur->type == WORD)
			(*argv_len)++;
		cur = cur->next;
	}
	return (1);
}

int	set_argv_val(t_cmd *cmd, t_token *cur, int idx, t_shell_data *data)
{
	if (!cmd || !cur)
		return (-1);
	if (cur->quote_status == s_q)
		cmd->argv[idx] = ft_strdup(cur->val);
	else
		cmd->argv[idx] = expand_str(cur->val, data);
	if (!cmd->argv[idx])
	{
		free_cmd_node(cmd);
		return (perror("malloc failed in set_argv_val()\n"), -1);
	}
	return (1);
}

int	set_fd(t_token *cur, t_cmd *cmd)
{
	if (!cur || !cmd)
		return (-1);
	if (cur->type == REDIRECT_IN)
		cmd->infile = open(cur->next->val, O_RDONLY);
	else if (cur->type == HERE_DOC)
		cmd->infile = here_doc(cur->next->val, &cmd->filepath);
	else if (cur->type == REDIRECT_OUT)
		cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cur->type == REDIRECT_APPEND)
		cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | \
			O_APPEND, 0644);
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:37:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/28 13:45:23 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_syntax(t_token **head);
int	get_argv_set_fd(t_cmd *cmd, t_token *start, int *argv_len);

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
				cmd->infile = here_doc(cur->next->val, cmd->temp_file);
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

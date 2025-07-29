/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:37:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/29 10:17:04 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		valid_syntax(t_token **head);
int		get_argv_set_fd(t_cmd *cmd, t_token *start, int *argv_len);
void	invalid_fd(int infile_fd, int outfile_fd);
void	set_fd(t_token *cur, t_cmd *cmd);

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
			set_fd(cur, cmd);
			cur = cur->next->next;
			if (cmd->infile < 0 || cmd->outfile < 0)
				return (invalid_fd(cmd->infile, cmd->outfile), ERR);
			continue ;
		}
		if (cur->type == WORD)
			(*argv_len)++;
		cur = cur->next;
	}
	return (1);
}

void	invalid_fd(int infile_fd, int outfile_fd)
{
	if (infile_fd > 0 && infile_fd != STDIN_FILENO)
		close(infile_fd);
	if (outfile_fd > 0 && outfile_fd != STDOUT_FILENO)
		close(outfile_fd);
	ft_putstr_fd("get_argv_set_fd()/open file failed\n", 2);
}

void	set_fd(t_token *cur, t_cmd *cmd)
{
	if (!cur || !cmd)
		return ;
	if (cur->type == REDIRECT_IN)
		cmd->infile = open(cur->next->val, O_RDONLY);
	else if (cur->type == HERE_DOC)
		cmd->infile = here_doc(cur->next->val, cmd->filepath);
	else if (cur->type == REDIRECT_OUT)
		cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cur->type == REDIRECT_APPEND)
		cmd->outfile = open(cur->next->val, O_CREAT | O_WRONLY | \
			O_APPEND, 0644);
}

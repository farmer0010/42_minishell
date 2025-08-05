/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/05 13:13:10 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_token **head)
{
	t_token	*cur;
	t_token	*temp;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		temp = cur;
		free(temp->val);
		cur = cur->next;
		free(temp);
	}
	*head = NULL;
}

void	invalid_fd(t_cmd *cmd)
{
	if (cmd->filepath != NULL)
	{
		unlink(cmd->filepath);
		free(cmd->filepath);
		cmd->filepath = NULL;
	}
	if (cmd->infile > 2)
	{
		close(cmd->infile);
		cmd->infile = 0;
	}
	if (cmd->outfile > 2)
	{
		close(cmd->outfile);
		cmd->outfile = 1;
	}
	ft_putstr_fd("minishell: ", 2);
}

void	case_invalid_fd(t_cmd *cmd, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	invalid_fd(cmd);
	cmd->redirect_error = 1;
	if (g_exit_status != 130)
		g_exit_status = 1;
}

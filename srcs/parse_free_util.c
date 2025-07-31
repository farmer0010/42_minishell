/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/31 11:32:44 by taewonki         ###   ########.fr       */
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
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
	ft_putstr_fd("in redirect token, open() is failed\n", 2);
}

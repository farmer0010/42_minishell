/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/29 13:49:28 by taewonki         ###   ########.fr       */
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

void	invalid_fd(int infile_fd, int outfile_fd)
{
	if (infile_fd > 2 && infile_fd != -1)
		close(infile_fd);
	if (outfile_fd > 2 && outfile_fd != -1)
		close(outfile_fd);
	ft_putstr_fd("get_argv_set_fd()/open file failed\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/22 13:21:57 by taewonki         ###   ########.fr       */
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
		free(cur->val);
		cur = cur->next;
		free(temp);
	}
	*head = NULL;
}

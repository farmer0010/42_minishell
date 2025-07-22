/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:25 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/21 17:54:27 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_node **head)
{
	t_node	*cur;
	t_node	*temp;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		cur = *head;
		temp = cur;
		free(cur->token->value);
		free(cur->token);
		cur = cur->next;
		free(temp);
	}
}

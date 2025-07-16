/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:56:05 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/16 10:57:56 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int type, char *value);
void	append_token(t_node **head, t_node *node);

t_node	*create_node(int type, char *value)
{
	t_node	*node;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("list_func.c/fail malloc() token\n");
		return (NULL);
	}
	token->type = type;
	token->value = value;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		perror("list_func.c/fail malloc() new_node\n");
		return (NULL);
	}
	node->token = token;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_token(t_node **head, t_node *node)
{
	if (!node || !head)
	{
		printf("list_func.c/append_token error\n");
		return ;
	}
	if (!*head)
	{
		head = node;
	}
	else
	{
		while (head->next)
		{
			head = head->next;
		}
		head->next = node;
		node->prev = head;
	}
}

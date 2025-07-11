/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:56:05 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/11 00:56:39 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int type, char *value)
{
	t_node	*node;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("fail malloc() token\n");
		return (NULL);
	}
	token->type = type;
	token->value = value;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		perror("fail malloc() new_node\n");
		return (NULL);
	}
	node->token = token;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_node(t_node **head, t_node *new_node)
{
	t_node	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->prev = current;
}

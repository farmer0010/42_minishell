/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:56:05 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/21 18:22:05 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int type, t_quote_type q, char *value);
void	append_token(t_node **head, t_node *node);

t_node	*create_node(int type, t_quote_type q, char *value)
{
	t_node	*node;
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (perror("fail malloc() token\n"), NULL);
	token->type = type;
	token->quote_status = q;
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), perror("malloc()token->value fail"), NULL);
	free(value);
	node = malloc(sizeof(t_node));
	if (!node)
		perror("fail malloc() node in create_node()");
	if (!node)
		return (free(token->value), free(token), NULL);
	node->token = token;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	append_token(t_node **head, t_node *node)
{
	t_node	*cur;

	if (!node || !head)
	{
		printf("list_func.c/append_token error\n");
		return (0);
	}
	if (!*head)
	{
		*head = node;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	node->prev = cur;
	return (1);
}

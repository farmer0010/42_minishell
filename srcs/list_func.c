/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:56:05 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/29 13:11:18 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(int type, t_quote_type q, char *val);
int		append_token(t_token **head, t_token *token);
t_token	*last_token(t_token *head);
t_cmd	*get_last_cmd(t_cmd *head);

t_token	*create_token(int type, t_quote_type q, char *val)
{
	t_token	*token;

	if (!val)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (perror("fail malloc() token\n"), NULL);
	token->type = type;
	token->quote_status = q;
	token->val = ft_strdup(val);
	free(val);
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_token	*last_token(t_token *head)
{
	t_token	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

int	append_token(t_token **head, t_token *token)
{
	t_token	*cur;

	if (!head || !token)
	{
		printf("list_func.c/append_token error\n");
		return (0);
	}
	if (!*head)
	{
		*head = token;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = token;
	token->prev = cur;
	return (1);
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	t_cmd	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

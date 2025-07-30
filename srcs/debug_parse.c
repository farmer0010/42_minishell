/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:09:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/30 11:26:12 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_lst(t_token *head)
{
	if (!head)
		return ;
	t_token	*cur = head;
	int i = 0;
	printf("--------------------------------------------------\n");
	while (cur)
	{
		printf("token [%d]", i);
		if (cur->type == PIPE)
			printf("token type : PIPE\n");
		else if (cur->type == REDIRECT_IN)
			printf("token type : REDIRECT_IN\n");
		else if (cur->type == REDIRECT_OUT)
			printf("token type : REDIRECT_OUT\n");
		else if (cur->type == HERE_DOC)
			printf("token type : HERE_DOC\n");
		else if (cur->type == REDIRECT_APPEND)
			printf("token type : REDIRECT_IN\n");
		else if (cur->type == WORD)
			printf("token type : WORD\n");
		if (cur->quote_status == not_q)
			printf("quote state : no quote\n");
		else if (cur->quote_status == not_q)
			printf("quote state : single quote\n");
		else if (cur->quote_status == not_q)
			printf("quote state : double quote\n");
		printf("token value : %s", cur->val);
		i++;
		cur = cur->next;
	}
	printf("---------------------------------------------------\n");
}

void	print_argv(char **ag)
{
	int i = 0;
	while(){}
}

void	print_cmd_lst(t_cmd *head)
{

}

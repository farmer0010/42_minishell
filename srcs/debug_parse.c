/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:09:28 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/30 14:01:36 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_lst(t_token *head)
{
	if (!head)
		return ;
	t_token	*cur = head;
	int i = 0;
	while (cur)
	{
		printf("--------------------------------------------------\n");
		printf("token [%d]\n", i);
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
		else if (cur->quote_status == s_q)
			printf("quote state : single quote\n");
		else if (cur->quote_status == d_q)
			printf("quote state : double quote\n");
		printf("token value : %s\n", cur->val);
		printf("---------------------------------------------------\n");
		i++;
		cur = cur->next;
	}
}

static void	print_argv(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("argv[%d] : %s\n", i, argv[i]);
		i++;
	}
}

void print_cmd_lst(t_cmd *head)
{
	t_cmd *cur = head;
	if (!head)
	{
		printf("print_cmd_lst() nothing turned in\n");
		return ;
	}
	int i = 0;
	while (cur)
	{
		printf("--------------------------------------------------\n");
		printf("cmd node [%d]\n", i);
		if (cur->argv){
			printf("argv\n");
			print_argv(cur->argv);
		}
		if (cur->filepath)
			printf("here_doc temp file name : %s\n", cur->filepath);
		else if (cur->filepath == NULL)
			printf("filepath is null\n");
		printf("infile : %d\n outfile : %d\n", cur->infile, cur->outfile);
		cur = cur->next;
		i++;
		printf("--------------------------------------------------\n");
	}
}

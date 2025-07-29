/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:53:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/29 13:46:56 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv);
void	free_cmd_list(t_cmd *cmd_list);
void	free_cmd_node(t_cmd *node);
void	free_token_list(t_token *token_list);

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next_cmd;

	current = cmd_list;
	while (current)
	{
		next_cmd = current->next;
		if (current->argv)
			free_argv(current->argv);
		if (current->infile != -1 && current->infile > 2)
			close(current->infile);
		if (current->outfile != -1 && current->outfile > 2)
			close(current->outfile);
		if (current->filepath)
		{
			unlink(current->filepath);
			free(current->filepath);
		}
		free(current);
		current = next_cmd;
	}
}

void	free_cmd_node(t_cmd *node)
{
	if (!node)
		return ;
	if (node->argv)
		free_argv(node->argv);
	if (node->infile != -1 && node->infile > 2)
		close(node->infile);
	if (node->outfile != -1 && node->outfile > 2)
		close(node->outfile);
	if (node->filepath)
	{
		unlink(node->filepath);
		free(node->filepath);
	}
	free(node);
}

void	free_token_list(t_token *token_list)
{
	t_token	*current;
	t_token	*next_node;

	current = token_list;
	while (current)
	{
		next_node = current->next;
		if (current->val)
			free(current->val);
		free(current);
		current = next_node;
	}
}

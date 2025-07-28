/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:53:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:53:31 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (current->infile != -1)
			close(current->infile);
		if (current->outfile != -1)
			close(current->outfile);
		free(current);
		current = next_cmd;
	}
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

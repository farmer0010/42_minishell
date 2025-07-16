/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:56:32 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/16 12:11:53 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_pipes(int **pipefd, int count)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

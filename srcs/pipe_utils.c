/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:09:55 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/11 10:09:56 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**create_pipes(int count)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)malloc(sizeof(int *) * count);
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipefd[i])
			return (free_pipes(pipefd, i), NULL);
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			return (free_pipes(pipefd, i + 1), NULL);
		}
		i++;
	}
	return (pipefd);
}

void	free_pipes(int **pipefd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

void	setup_pipes(int idx, int count, int **pipefd)
{
	if (idx > 0)
	{
		if (dup2(pipefd[idx - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 in setup_pipes (read)");
			exit(EXIT_FAILURE);
		}
	}
	if (idx < count - 1)
	{
		if (dup2(pipefd[idx][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 in setup_pipes (write)");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_unused_pipes(int **pipefd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

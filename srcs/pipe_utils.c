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

#include "minishell.h"

int	**create_pipes(int count)
{
	int		**pipefd;
	int		i;

	if (count <= 0)
		return (NULL);
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
			perror("minishell: pipe failed");
			return (free_pipes(pipefd, i + 1), NULL);
		}
		i++;
	}
	return (pipefd);
}

void	setup_pipes(int idx, int count, int **pipefd)
{
	if (! pipefd || ! *pipefd)
		return ;
	if (idx > 0)
	{
		if (dup2(pipefd[idx - 1][0], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 (pipe read end) failed");
			exit(EXIT_FAILURE);
		}
		close(pipefd[idx - 1][0]);
	}
	if (idx < count - 1)
	{
		if (dup2(pipefd[idx][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 (pipe write end) failed");
			exit(EXIT_FAILURE);
		}
		close(pipefd[idx][1]);
	}
}

void	close_all_pipe_fds_in_child(int **pipefd, int count)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipefd[i][0] != -1)
			close(pipefd[i][0]);
		if (pipefd[i][1] != -1)
			close(pipefd[i][1]);
		i++;
	}
}

void	close_unused_pipes(int **pipefd, int count)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

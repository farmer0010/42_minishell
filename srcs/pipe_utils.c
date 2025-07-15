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

int **create_pipes(int count)
{
    int **pipefd;
    int i;

    pipefd = (int **)malloc(sizeof(int *) * count);
    if (!pipefd)
        return (NULL);
    i = 0;
    while (i < count)
    {
        pipefd[i] = (int *)malloc(sizeof(int) * 2);
        if (!pipefd[i])
        {
            free_pipes(pipefd, i);
            return (NULL);
        }
        if (pipe(pipefd[i]) == -1)
        {
            perror("pipe");
            free_pipes(pipefd, i + 1);
            return (NULL);
        }
        i++;
    }
    return (pipefd);
}

void	close_pipes(int **pipefd, int count)
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



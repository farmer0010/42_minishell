/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:49:44 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/11 10:49:46 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	setup_pipes(int idx, int count, int **pipefd)
{
	if (idx > 0)
	{
		if(dup2(pipefd[idx - 1][0], STDIN_FILENO) == - 1)
		{
			perror("dup2 in setup_pipes (read)");
			exit(EXIT_FAILURE);
		}
	}
	if (idx < count - 1)
	{
		if(dup2(pipefd[idx][1],STDOUT_FILENO) == -1)
		{
			perror("dup2 in setup_pipes (write)");
			exit(EXIT_FAILURE);
		}
	}
}

void	child_process(t_cmd *cmd, int idx, int count, int **pipefd)
{
	char *exec_path;

	setup_pipes(idx, count, pipefd);
	if (handle_redirects(cmd))
		exit(EXIT_FAILURE);
	exec_path = find_executable(cmd->argv[0], environ);
	if (!exec_path)
    {
        write(2, "minishell: command not found: ", 31);
        write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
        write(2, "\n", 1);
        exit(127);
    }
	execve(exec_path, cmd -> argv, environ);
	perror("execve");
	free(exec_path);
	exit(EXIT_FAILURE);
}

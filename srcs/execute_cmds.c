/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:30:38 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/10 09:30:40 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ; // 시스템에서 이미 전역으로 제공하는 환경변수 배열 포인터

static int fork_and_execute(char *exec_path, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(exec_path, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

void execute_cmds(t_cmd *cmd)
{
	char *exec_path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	exec_path = find_executable(cmd->argv[0], environ);
	if (!exec_path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		return ;
	}
	fork_and_execute(exec_path, cmd->argv, environ);
	free(exec_path);
}

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

int	fork_and_execute(char *exec_path, char **argv, char **envp, t_cmd *cmd)
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
		if (handle_redirects(cmd))
			exit(EXIT_FAILURE);
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

static int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	wait_all_children(int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		wait(&status);
		i++;
	}
}

void	execute_cmds(t_cmd *cmd)
{
	int		count;
	int		**pipefd;
	pid_t	pid;
	int		idx;
	t_cmd	*curr;

	count = count_commands(cmd);
	pipefd = create_pipes(count - 1);
	if (!pipefd)
		return ;
	idx = 0;
	curr = cmd;
	while (curr)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
			child_process(curr, idx, count, pipefd);
		curr = curr->next;
		idx++;
	}
	close_pipes(pipefd, count - 1);
	wait_all_children(count);
	free_pipes(pipefd, count - 1);
}

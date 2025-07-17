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

void	child_process(t_cmd *cmd, int idx, int count, int **pipefd)
{
	char	*exec_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	execve(exec_path, cmd->argv, environ);
	perror("execve");
	free(exec_path);
	exit(EXIT_FAILURE);
}

void	run_child_processes(t_cmd *cmd, int count, int **pipefd)
{
	pid_t	pid;
	int		idx;
	t_cmd	*curr;

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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:26:32 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:26:41 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cmd *cmd)
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

static void	wait_all_children(int count, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	waited_pid;

	i = 0;
	while (i < count)
	{
		waited_pid = wait(&status);
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static int	init_pipe_data(t_shell_data *data, int num_cmds)
{
	data->pipe_data.count = num_cmds;
	data->pipe_data.idx = 0;
	data->pipe_data.pipefd = create_pipes(num_cmds - 1);
	if (!data->pipe_data.pipefd && num_cmds > 1)
	{
		perror("minishell: failed to create pipes");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static pid_t	fork_commands(t_shell_data *data, t_cmd *cmd_list)
{
	t_cmd	*curr;
	pid_t	last_pid;

	curr = cmd_list;
	while (curr)
	{
		last_pid = fork();
		if (last_pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (last_pid == 0)
			child_process(curr, data);
		curr = curr->next;
		data->pipe_data.idx++;
	}
	return (last_pid);
}

int	handle_multiple_cmds(t_shell_data *data, t_cmd *cmd_list)
{
	int		num_cmds;
	pid_t	last_pid;

	num_cmds = count_commands(cmd_list);
	if (init_pipe_data(data, num_cmds))
		return (g_exit_status);
	last_pid = fork_commands(data, cmd_list);
	if (last_pid == -1)
		return (1);
	close_unused_pipes(data->pipe_data.pipefd, num_cmds - 1);
	free_pipes(data->pipe_data.pipefd, num_cmds - 1);
	data->pipe_data.pipefd = NULL;
	wait_all_children(num_cmds, last_pid);
	return (g_exit_status);
}

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
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		i++;
	}
}

void	handle_multiple_cmds(t_shell_data *data, t_cmd *cmd_list)
{
	int	num_cmds;

	num_cmds = count_commands(cmd_list);
	data->pipe_data.count = num_cmds;
	data->pipe_data.idx = 0;
	data->pipe_data.pipefd = create_pipes(num_cmds - 1);
	if (!data->pipe_data.pipefd)
	{
		perror("minishell: failed to create pipes");
		g_exit_status = 1;
		return ;
	}
	run_child_processes(cmd_list, data);
	close_unused_pipes(data->pipe_data.pipefd, num_cmds - 1);
	free_pipes(data->pipe_data.pipefd, num_cmds - 1);
	data->pipe_data.pipefd = NULL;
	wait_all_children(num_cmds);
}

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

#include "minishell.h"

int	handle_single_external_cmd(t_shell_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (g_exit_status = EXIT_FAILURE);
	}
	if (pid == 0)
	{
		child_process(data->cmd_list, data);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (g_exit_status = EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	return (g_exit_status);
}

int	execute_cmds(t_shell_data *data)
{
	int	num_cmds;

	if (!data->cmd_list)
		return (0);
	num_cmds = count_commands(data->cmd_list);
	data->pipe_data.pipefd = NULL;
	data->pipe_data.count = num_cmds;
	if (num_cmds == 1)
	{
		if (is_builtin(data->cmd_list->argv[0]))
			return (handle_single_builtin(data->cmd_list, data));
		else
			return (handle_single_external_cmd(data));
	}
	else
		return (handle_multiple_cmds(data, data->cmd_list));
}

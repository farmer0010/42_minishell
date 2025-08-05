/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:00:00 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/11 11:00:00 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	setup_child_pipes(t_shell_data *data)
{
	setup_pipes(data->pipe_data.idx,
		data->pipe_data.count, data->pipe_data.pipefd);
}

void	exec_command(t_cmd *cmd, t_shell_data *data)
{
	char	*path;

	path = get_exec_path(cmd, data);
	handle_execve(path, cmd->argv, data);
}

void	child_process(t_cmd *cmd, t_shell_data *data)
{
	if (cmd -> redirect_error)
		exit(1);
	setup_child_signals();
	setup_child_pipes(data);
	close_all_pipe_fds_in_child(data->pipe_data.pipefd,
		data->pipe_data.count - 1);
	if (handle_redirects(cmd))
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->argv[0]))
	{
		g_exit_status = exec_builtin(cmd, data);
		free_all(data);
		exit(g_exit_status);
	}
	exec_command(cmd, data);
}

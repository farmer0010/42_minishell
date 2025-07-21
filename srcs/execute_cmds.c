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

void	execute_cmds(t_shell_data *data)
{
	t_cmd	*cmd_list;
	int		num_cmds;

	cmd_list = data->cmd_list;
	if (!cmd_list || !cmd_list->argv || !cmd_list->argv[0])
	{
		g_exit_status = 0;
		return ;
	}
	if (!cmd_list->next && is_builtin(cmd_list->argv[0]))
	{
		data->stdin_backup = dup(STDIN_FILENO);
		data->stdout_backup = dup(STDOUT_FILENO);
		if (data->stdin_backup == -1 || data->stdout_backup == -1)
		{
			perror("minishell: dup failed");
			if (data->stdin_backup != -1)
				close(data->stdin_backup);
			if (data->stdout_backup != -1)
				close(data->stdout_backup);
			g_exit_status = 1;
			return ;
		}
		if (handle_redirects(cmd_list))
		{
			g_exit_status = 1;
			if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
				perror("minishell: dup2 restore stdin failed");
			if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
				perror("minishell: dup2 restore stdout failed");
			close(data->stdin_backup);
			close(data->stdout_backup);
			return ;
		}
		g_exit_status = exec_builtin(cmd_list, data);
		if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
			perror("minishell: dup2 restore stdin failed");
		if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
			perror("minishell: dup2 restore stdout failed");
		close(data->stdin_backup);
		close(data->stdout_backup);
		return ;
	}
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


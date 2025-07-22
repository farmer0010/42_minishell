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

#include "minishell.h"

void	child_process(t_cmd *cmd, t_shell_data *data)
{
	char	*exec_path;
	char	**env_array;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes(data->pipe_data.idx, data->pipe_data.count, data->pipe_data.pipefd);
	close_unused_pipes(data->pipe_data.pipefd, data->pipe_data.count - 1);
	if (handle_redirects(cmd))
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	if (is_builtin(cmd->argv[0]))
	{
		g_exit_status = exec_builtin(cmd, data);
		free_all(data);
		exit(g_exit_status);
	}
	exec_path = find_executable(cmd->argv[0], data->env_list);
	if (!exec_path)
	{
		write(2, "minishell: command not found: ", 31);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		free_all(data);
		exit(127);
	}
	env_array = convert_env_list_to_array(data->env_list);
	if (!env_array)
	{
		perror("minishell: failed to convert env list to array");
		free(exec_path);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	execve(exec_path, cmd->argv, env_array);
	perror("minishell: execve failed");
	free(exec_path);
	free_env_array(env_array);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	run_child_processes(t_cmd *cmd_list, t_shell_data *data)
{
	pid_t	pid;
	t_cmd	*curr;

	data->pipe_data.idx = 0;
	curr = cmd_list;
	while (curr)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork failed");
			close_unused_pipes(data->pipe_data.pipefd, data->pipe_data.count - 1);
			free_pipes(data->pipe_data.pipefd, data->pipe_data.count - 1);
			data->pipe_data.pipefd = NULL;
			g_exit_status = 1;
			return ;
		}
		else if (pid == 0)
			child_process(curr, data);
		curr = curr->next;
		data->pipe_data.idx++;
	}
}


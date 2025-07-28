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

static char	**prepare_exec_data(t_cmd *cmd,
	t_shell_data *data, char **exec_path)
{
	char	**env_array;

	*exec_path = find_executable(cmd->argv[0], data->env_list);
	if (!*exec_path)
		return (NULL);
	env_array = convert_env_list_to_array(data->env_list);
	if (!env_array)
	{
		free(*exec_path);
		return (NULL);
	}
	return (env_array);
}

static void	exec_command(t_cmd *cmd, t_shell_data *data)
{
	char	*exec_path;
	char	**env_array;

	env_array = prepare_exec_data(cmd, data, &exec_path);
	if (!env_array)
	{
		if (!exec_path)
		{
			write(2, "minishell: command not found: ", 30);
			write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
			write(2, "\n", 1);
			free_all(data);
			exit(127);
		}
		perror("minishell: failed to convert env list to array");
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

void	child_process(t_cmd *cmd, t_shell_data *data)
{
	setup_child_signals();
	setup_child_pipes(data);
	close_all_pipe_fds_in_child(data->pipe_data.pipefd,
		data->pipe_data.count - 1);
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
	exec_command(cmd, data);
}

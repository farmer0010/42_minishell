/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:04:06 by juyoukim          #+#    #+#             */
/*   Updated: 2025/08/01 12:04:07 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_and_exit(char *cmd, char *msg, int exit_code, t_shell_data *data)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	free_all(data);
	exit(exit_code);
}

static char	*handle_direct_path(char *cmd_path, t_shell_data *data)
{
	if (access(cmd_path, F_OK) == -1)
		print_error_and_exit(cmd_path, ": No such file or directory\n", 127, data);
	if (access(cmd_path, X_OK) == -1)
		print_error_and_exit(cmd_path, ": Permission denied\n", 126, data);
	char *exec_path = ft_strdup(cmd_path);
	if (!exec_path)
	{
		perror("minishell: malloc failed");
		free_all(data);
		exit(EXIT_FAILURE);
	}
	return (exec_path);
}

char	*get_exec_path(t_cmd *cmd, t_shell_data *data)
{
	char	*exec_path;

	if (ft_strchr(cmd->argv[0], '/'))
		exec_path = handle_direct_path(cmd->argv[0], data);
	else
	{
		exec_path = find_executable(cmd->argv[0], data->env_list);
		if (!exec_path)
			print_error_and_exit(cmd->argv[0], ": command not found\n", 127, data);
	}
	return (exec_path);
}

void	handle_execve(char *path, char **argv, t_shell_data *data)
{
	char	**envp;

	envp = convert_env_list_to_array(data->env_list);
	if (!envp)
	{
		perror("minishell: env malloc fail");
		free(path);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	execve(path, argv, envp);
	perror("minishell");
	if (errno == EACCES)
		g_exit_status = 126;
	else if (errno == ENOENT)
		g_exit_status = 127;
	else
		g_exit_status = EXIT_FAILURE;
	free(path);
	free_env_array(envp);
	free_all(data);
	exit(g_exit_status);
}


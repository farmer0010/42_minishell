/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:26:06 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:26:07 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_std_fds(t_shell_data *data)
{
	dup2(data->stdin_backup, STDIN_FILENO);
	dup2(data->stdout_backup, STDOUT_FILENO);
	close(data->stdin_backup);
	close(data->stdout_backup);
}

int	handle_single_builtin(t_cmd *cmd, t_shell_data *data)
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
		return (g_exit_status);
	}
	if (handle_redirects(cmd))
	{
		g_exit_status = 1;
		restore_std_fds(data);
		return (g_exit_status);
	}
	g_exit_status = exec_builtin(cmd, data);
	restore_std_fds(data);
	return (g_exit_status);
}

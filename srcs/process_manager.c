/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:34:36 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:34:37 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			close_unused_pipes(data->pipe_data.pipefd,
				data->pipe_data.count - 1);
			free_pipes(data->pipe_data.pipefd,
				data->pipe_data.count - 1);
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

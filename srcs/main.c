/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:20:34 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/10 09:20:35 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	data;

	(void)argc;
	(void)argv;
	data.env_list = NULL;
	data.cmd_list = NULL;
	data.token_list = NULL;
	data.stdin_backup = -1;
	data.stdout_backup = -1;
	data.pipe_data.pipefd = NULL;
	data.env_list = init_env_list(envp);
	if (!data.env_list)
		return (1);
	start_minishell(&data);
	free_all(&data);
	return (g_exit_status);
}

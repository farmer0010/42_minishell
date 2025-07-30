/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:51:24 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/30 09:51:26 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_init_error(void)
{
	perror("minishell: Failed to initialize environment");
}

int	init_shell_data(t_shell_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_shell_data));
	data->stdin_backup = -1;
	data->stdout_backup = -1;
	data->env_list = init_env_list(envp);
	if (!data->env_list)
		return (0);
	return (1);
}

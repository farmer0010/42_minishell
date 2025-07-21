/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:47:20 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/13 14:47:22 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "export") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "env") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_builtin(t_cmd *cmd, t_shell_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, data->env_list));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, &(data->env_list)));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, &(data->env_list)));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(data->env_list));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv, data));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:21:47 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 16:21:50 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_oldpwd(t_shell_data *data)
{
	char	old_pwd[4096];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd failed");
		g_exit_status = 1;
		return (1);
	}
	if (set_env_value(&(data->env_list), "OLDPWD", old_pwd) != 0)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static void	print_cd_error(char *msg)
{
	write(2, "minishell: cd: ", 15);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_exit_status = 1;
}

static char	*get_target_path(char **argv, t_shell_data *data)
{
	char	*target_path;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		target_path = get_env_value(data->env_list, "HOME");
		if (!target_path)
		{
			print_cd_error("HOME not set");
			return (NULL);
		}
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		target_path = get_env_value(data->env_list, "OLDPWD");
		if (!target_path)
		{
			print_cd_error("OLDPWD not set");
			return (NULL);
		}
		printf("%s\n", target_path);
	}
	else
		target_path = argv[1];
	return (target_path);
}

static int	change_directory(char *target_path, t_shell_data *data)
{
	char	new_pwd[4096];

	if (chdir(target_path) == -1)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd failed");
		g_exit_status = 1;
		return (1);
	}
	if (set_env_value(&(data->env_list), "PWD", new_pwd) != 0)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(char **argv, t_shell_data *data)
{
	char	*target_path;
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	if (get_oldpwd(data))
		return (1);
	target_path = get_target_path(argv, data);
	if (!target_path)
		return (1);
	if (change_directory(target_path, data))
		return (1);
	g_exit_status = 0;
	return (0);
}

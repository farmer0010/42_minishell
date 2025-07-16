/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:09 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/14 10:21:11 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strchr(environ[i], '='))
			printf("declare -x %s\n", environ[i]);
		i++;
	}
}

static void	handle_export_arg(const char *arg)
{
	if (! is_valid_identifier(arg))
	{
		write(2, "minishell: export: not a valid identifier\n", 43);
		return ;
	}
	if (!ft_strchr(arg, '='))
		return ;
	putenv(ft_strdup(arg));
}

int	builtin_export(char **argv)
{
	int	i;

	if (! argv[1])
	{
		print_export_env();
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		handle_export_arg(argv[i]);
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (! is_valid_identifier(argv[i]))
		{
			write(2, "minishell: export: not a valid identifier\n", 43);
			return ;
		}
	}
}

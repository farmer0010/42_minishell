/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:09 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/14 10:21:11 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

static int	is_valid_identifier(const char *str)
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

static int	starts_with(const char *str, const char *prefix)
{
	int	i;

	i = 0;
	while (prefix[i])
	{
		if (prefix[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	return (0);
}

static void	remove_env_var(const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (environ[i])
	{
		if (starts_with(environ[i], name))
		{
			free(environ[i]);
			j = i;
			while (environ[j])
			{
				environ[j] = environ[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}

int	builtin_unset(char **argv)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			write(2, "minishell: unset: not a valid identifier\n", 41);
			return (1);
		}
		remove_env_var(argv[i]);
		i++;
	}
	return (0);
}

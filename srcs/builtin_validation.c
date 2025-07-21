/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:21:09 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/14 10:21:11 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
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

void	handle_export_key_value(t_list **env_list, char *key, char *value)
{
	if (set_env_value(env_list, key, value) == -1)
	{
		perror("minishell: export: set_env_value failed");
		g_exit_status = 1;
	}
}

void	handle_export_with_value(t_list **env_list, const char *arg
	, char *equal_sign)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_sign - arg);
	value = equal_sign + 1;
	if (!key)
	{
		perror("minishell: export: malloc failed");
		g_exit_status = 1;
		return ;
	}
	handle_export_key_value(env_list, key, value);
	free(key);
}

void	handle_export_no_value(t_list **env_list, const char *arg)
{
	char	*key;

	key = ft_strdup(arg);
	if (!key)
	{
		perror("minishell: export: malloc failed");
		g_exit_status = 1;
		return ;
	}
	handle_export_key_value(env_list, key, "");
	free(key);
}

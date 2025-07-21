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

static void	print_export_env(t_list *env_list)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		printf("declare -x %s", env->key);
		if (env->value && ft_strlen(env->value) > 0)
			printf("=\"%s\"", env->value);
		printf("\n");
		current = current->next;
	}
}

static void	handle_export_arg(const char *arg, t_list **env_list)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		g_exit_status = 1;
		return ;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = equal_sign + 1;
		if (!key)
		{
			perror("minishell: export: malloc failed");
			g_exit_status = 1;
			return ;
		}
		if (set_env_value(env_list, key, value) == -1)
		{
			perror("minishell: export: set_env_value failed");
			g_exit_status = 1;
		}
		free(key);
	}
	else
	{
		key = ft_strdup(arg);
		if (!key)
		{
			perror("minishell: export: malloc failed");
			g_exit_status = 1;
			return ;
		}
		if (set_env_value(env_list, key, "") == -1)
		{
			perror("minishell: export: set_env_value failed");
			g_exit_status = 1;
		}
		free(key);
	}
}

int	builtin_export(char **argv, t_list *env_list)
{
	int	i;
	int	ret_status;

	ret_status = 0;
	if (!argv[1])
	{
		print_export_env(env_list);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		handle_export_arg(argv[i], &env_list);
		if (g_exit_status == 1)
			ret_status = 1;
		g_exit_status = 0;
		i++;
	}
	return (ret_status);
}


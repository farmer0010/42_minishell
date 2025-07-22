/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:48:08 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:48:12 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_export_arg(const char *arg, t_list **env_list)
{
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
		handle_export_with_value(env_list, arg, equal_sign);
	else
		handle_export_no_value(env_list, arg);
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

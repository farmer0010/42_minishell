/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:27:04 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/13 16:27:05 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:27:04 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/13 16:27:05 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_option(const char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (FALSE);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = TRUE;
	while (argv[i] && is_valid_n_option(argv[i]))
	{
		newline_flag = FALSE;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline_flag)
		printf("\n");
	g_exit_status = 0;
	return (0);
}

int	builtin_cd(char **argv, t_list *env_list)
{
	char	*path;

	if (!argv[1])
	{
		path = get_env_value(env_list, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			g_exit_status = 1;
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		perror("minishell: pwd");
		g_exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd);
	g_exit_status = 0;
	return (0);
}

int	builtin_env(t_list *env_list)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		current = current->next;
	}
	g_exit_status = 0;
	return (0);
}

int	builtin_exit(char **argv, t_shell_data *data)
{
	long long	exit_code;

	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 28);
			free_all(data);
			exit(255);
		}
		if (argv[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_exit_status = 1;
			return (1);
		}
		exit_code = ft_atoll(argv[1]);
		exit_code = (exit_code % 256 + 256) % 256;
	}
	else
		exit_code = g_exit_status;
	free_all(data);
	exit(exit_code);
}



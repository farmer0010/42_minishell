/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:27:04 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/16 18:05:02 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	builtin_echo(char **argv)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		newline_flag = 0;
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
	return (0);
}

int	builtin_cd(char **argv)
{
	char	*path;

	if (! argv[1])
	{
		path = getenv("HOME");
		if (! path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = malloc(4096);
	if (! cwd)
		return (1);
	if (getcwd(cwd, 4096) == NULL)
	{
		perror("minishell: pwd");
		free(cwd);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	builtin_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strchr(environ[i], "="))
			printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(char **argv)
{
	int	exit_code;

	printf("exit\n");
	if (! argv[1])
		exit(0);
	if (! is_numeric(argv[1]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		exit(255);
	}
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	exit(exit_code);
}

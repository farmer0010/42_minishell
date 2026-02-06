/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_pwd.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:41:45 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 13:41:47 by juyoukim         ###   ########.fr       */
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

static int	parse_n_option(char **argv, int *i)
{
	int	newline_flag;

	newline_flag = TRUE;
	while (argv[*i])
	{
		if (ft_strcmp(argv[*i], "--") == 0)
		{
			(*i)++;
			break ;
		}
		if (is_valid_n_option(argv[*i]))
			newline_flag = FALSE;
		else
			break ;
		(*i)++;
	}
	return (newline_flag);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = parse_n_option(argv, &i);
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

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: pwd");
		g_exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd);
	g_exit_status = 0;
	return (0);
}

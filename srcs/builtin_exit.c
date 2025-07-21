/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:57:51 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 15:57:58 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_numeric_error(char *arg, t_shell_data *data)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	free_all(data);
	exit(255);
}

static int	exit_too_many_args(void)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	g_exit_status = 1;
	return (1);
}

int	builtin_exit(char **argv, t_shell_data *data)
{
	long long	exit_code;

	printf("exit\n");
	if (argv[1])
	{
		errno = 0;
		exit_code = ft_atoll(argv[1]);
		if (errno == ERANGE || errno == EINVAL)
			exit_numeric_error(argv[1], data);
		if (argv[2])
			return (exit_too_many_args());
		exit_code = (exit_code % 256 + 256) % 256;
	}
	else
		exit_code = g_exit_status;
	free_all(data);
	exit(exit_code);
}

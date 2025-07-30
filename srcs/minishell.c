/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:25:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/16 13:13:09 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell_data	data;

	(void)ac;
	(void)av;
	if (!init_shell_data(&data, envp))
	{
		print_init_error();
		return (EXIT_FAILURE);
	}
	start_minishell(&data);
	free_all(&data);
	return (g_exit_status);
}

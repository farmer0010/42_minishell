/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:25:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/31 11:54:44 by taewonki         ###   ########.fr       */
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
		g_exit_status = EXIT_FAILURE;
		return (g_exit_status);
	}
	start_minishell(&data);
	free_all(&data);
	return (g_exit_status);
}

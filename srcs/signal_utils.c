/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:06:54 by juyoukim          #+#    #+#             */
/*   Updated: 2025/08/04 14:56:43 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_exit_status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signo)
{
	(void)signo;
}

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 130;
	rl_done = 1;
}

int	null_event_hook(void)
{
	return (0);
}

int heredoc_event_hook(void)
{
	if (g_exit_status == 130)
	{
		rl_done = 1;
		return (-1);
	}
	return 0;
}

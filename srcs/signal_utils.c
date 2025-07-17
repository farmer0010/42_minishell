/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:06:54 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/17 11:06:56 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_exit_status = 130;
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signo)
{
	(void)signo;
}

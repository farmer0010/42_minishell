/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:09:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/08/04 16:01:09 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_shell_data *data)
{
	char	*input;

	while (TRUE)
	{
		init_signal();
		input = read_user_input();
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!perform_lexing(data, input))
			continue ;
		if (!perform_parsing(data))
			continue ;
		execute_cmds(data);
		cleanup_cmd_data(data);
	}
}

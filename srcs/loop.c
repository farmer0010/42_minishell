/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:09:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/30 13:38:26 by taewonki         ###   ########.fr       */
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
		if (!perform_lexing(data, input)){
			print_token_lst(data->token_list);
			continue ;
		}
		if (!perform_parsing(data)){
			print_cmd_lst(data->cmd_list);
			continue ;
		}
		execute_cmds(data);
		cleanup_cmd_data(data);
	}
}

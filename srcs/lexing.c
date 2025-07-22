/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:21:02 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/22 10:12:57 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token_info(const char *cmd, t_node **head);

void	get_token_info(const char *cmd, t_node **head)
{
	t_state	state;
	int		i;

	i = 0;
	state = s_in_general;
	while (cmd[i])
	{
		if (state == s_in_general)
		{
			handle_general(cmd, &i, &state, head);
			continue ;
		}
		else if (state == s_in_single_quote)
		{
			handle_s_quote(cmd, &i, &state, head);
			continue ;
		}
		else if (state == s_in_double_quote)
		{
			handle_d_quote(cmd, &i, &state, head);
			continue;
		}
		else if (state == s_in_word)
		{
			handle_in_word(cmd, &i, &state, head);
			continue;
		}
	}
}

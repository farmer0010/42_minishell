/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:21:02 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/28 11:26:28 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token_info(const char *cmd, t_token **head);

void	get_token_info(const char *cmd, t_token **head)
{
	t_state	state;
	int		i;
	int		lex_status;

	i = 0;
	state = s_in_general;
	while (cmd[i])
	{
		if (state == s_in_general)
			lex_status = handle_general(cmd, &i, &state, head);
		else if (state == s_in_single_quote)
			lex_status = handle_s_quote(cmd, &i, &state, head);
		else if (state == s_in_double_quote)
			lex_status = handle_d_quote(cmd, &i, &state, head);
		else if (state == s_in_word)
			lex_status = handle_in_word(cmd, &i, &state, head);
		if (lex_status < 0)
		{
			ft_free_lst(head);
			return ;
		}
	}
}

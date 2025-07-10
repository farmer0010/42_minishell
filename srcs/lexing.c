/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:32:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/10 16:37:31 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexing(const char *cmd)
{
	char	*temp_cmd;
	int		word_len = 0;
	int		oper_len = 0;
	t_token	*token_ls;
	t_statemachine	machine;

	machine.s_in_general = 1;
	machine.s_in_double_quote = 0;
	machine.s_in_operation = 0;
	machine.s_in_single_quote = 0;
	machine.s_in_word = 0;
	token_ls = malloc(sizeof(t_token) * (ft_strlen(cmd) + 1));
	if (!token_ls)
	{
		perror("fail malloc() token_ls\n");
		return ;
	}
	while (1)
	{
		temp_cmd = cmd;
		while(ft_isspace(*temp_cmd))
			cmd++;
		if (ft_isalnum(*cmd))
		{
			machine.s_in_word ^= 1;
		}
		if (machine.s_in_word)
	}
}

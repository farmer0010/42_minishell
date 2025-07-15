/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:21:02 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/15 11:12:15 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	get_token_info(const char *cmd, t_node *tok)
{
	t_state state;
	char *temp;
	char *cmd_line;
	int token_len;

	state = s_in_general;
	temp = cmd;
	while (*temp)
	{
		while (ft_isspace(*temp))
		{
			temp++;
			if (*temp == '\0')
				return ;
		}
		if (ft_isquote(*temp))
		{
			if (ft_isquote(*temp) == 1)
			{
				temp++;
				state = s_in_single_quote;
				token_len = ft_strchr(temp, '\'') - temp;
				ft_strlcpy(tok->token->value ,temp, token_len + 1);
				tok->token->type = WORD;
				temp += token_len + 1;
			}
			else if (ft_isquote(*temp) == 2)
			{
				temp++;
				state = s_in_double_quote;
				token_len = ft_strchr(temp, '\"') - temp;
				tok->token->value = ft_strlcpy(tok->token->value,temp, token_len + 1);
				tok->token->type = WORD;
				temp += token_len + 1;
			}
			else if (ft_isoper(*temp))
			{
				state = s_in_operation;
				if (*temp == '|')
				{
					tok->token->type = PIPE;
					ft_strlcpy(tok->token->value, "|", 2);
					temp++;
				}
				else if (*temp == '<')
				{
					temp++;
					if (*temp == '<')
					{
						tok->token->type = HERE_DOC;
						ft_strlcpy(tok->token->value, "<<", 3);
						temp++;
					}
					else
					{
						tok->token->type = REDIRECT_IN;
						ft_strlcpy(tok->token->value, "<", 2);
					}
				}
				else if (*temp == '>')
				{
					temp++;
					if (*temp == '>')
					{
						tok->token->type = REDIRECT_APPEND;
						ft_strlcpy(tok->token->value, ">>", 3);
						temp++;
					}
					else
					{
						tok->token->type = REDIRECT_OUT;
						ft_strlcpy(tok->token->value, ">", 2);
					}
				}
			}
		}
	}
}



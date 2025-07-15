/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:54:14 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/15 10:35:50 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c > 9 && c < 14)
		return (1);
	else
		return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}

int	ft_isoper(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

char	handle_escape(char c)
{
if (c == 'n')
		return ('\n');
	else if (c == 't')
		return ('\t');
	else if (c == 'r')
		return ('\r');
	else if (c == 'v')
		return ('\v');
	else if (c == 'f')
		return ('\f');
	else if (c == '\"')
		return ('\"');
	else if (c == ' ')
		return (' ');
	else if (c == '\\')
		return ('\\');
	else if (c == '\'')
		return ('\'');
	else
		return (c);
}

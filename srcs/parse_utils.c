/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:54:14 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/28 11:25:20 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isquote(char c);
int		ft_isspace(char c);
int		ft_isoper(char c);

int		ft_isspace(char c)
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
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIRECT_IN);
	else if (c == '>')
		return (REDIRECT_OUT);
	else
		return (0);
}

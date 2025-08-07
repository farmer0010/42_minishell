/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handler_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:51:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/07 12:58:45 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_token(int *i, t_token **head);
int	handle_redirect_in_token(const char *cmd, int *i, t_token **head);
int	handle_redirect_out_token(const char *cmd, int *i, t_token **head);

int	handle_pipe_token(int *i, t_token **head)
{
	char	*val;
	t_token	*new_token;

	val = ft_strdup("|");
	if (!val)
		return (ft_putstr_fd("malloc() fail\n", 2), ERR);
	new_token = create_token(PIPE, not_q, val);
	if (token_error_handler(new_token, head) < 0)
		return (-1);
	(*i)++;
	return (PIPE);
}

int	handle_redirect_in_token(const char *cmd, int *i, t_token **head)
{
	char	*val;
	int		token_type;

	if (cmd[*i + 1] && ft_isoper(cmd[*i + 1]) == REDIRECT_IN)
	{
		val = ft_strdup("<<");
		token_type = HERE_DOC;
		*i += 2;
	}
	else
	{
		val = ft_strdup("<");
		token_type = REDIRECT_IN;
		(*i)++;
	}
	if (!val)
		return (ft_putstr_fd("malloc() fail\n", 2), ERR);
	if (!token_error_handler(create_token(token_type, not_q, val), head))
		return (ERR);
	return (token_type);
}

int	handle_redirect_out_token(const char *cmd, int *i, t_token **head)
{
	char	*val;
	int		token_type;

	if (cmd[*i + 1] && ft_isoper(cmd[*i + 1]) == REDIRECT_OUT)
	{
		val = ft_strdup(">>");
		token_type = REDIRECT_APPEND;
		*i += 2;
	}
	else
	{
		val = ft_strdup(">");
		token_type = REDIRECT_OUT;
		(*i)++;
	}
	if (!val)
		return (ft_putstr_fd("malloc() fail\n", 2), ERR);
	if (!token_error_handler(create_token(token_type, not_q, val), head))
		return (ERR);
	return (token_type);
}

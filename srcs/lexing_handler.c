/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:13:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/05 14:20:55 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_general(const char *cmd, int *i, t_state *s, t_token **head);
int		handle_in_oper(const char *cmd, int *i, t_token **head);
int		handle_s_quote(const char *cmd, int *i, t_state *s, t_token **head);
int		handle_d_quote(const char *cmd, int *i, t_state *s, t_token **head);
int		handle_in_word(const char *cmd, int *i, t_state *s, t_token **head);

int	handle_in_oper(const char *cmd, int *i, t_token **head)
{
	if (ft_isoper(cmd[*i]) == PIPE)
		return (append_token(head, create_token(PIPE, not_q, \
			ft_strdup("|"))), (*i)++, PIPE);
	else if (ft_isoper(cmd[*i]) == REDIRECT_IN)
	{
		if (cmd[*i + 1] && ft_isoper(cmd[*i + 1]) == REDIRECT_IN)
			return (append_token(head, create_token(HERE_DOC, not_q, \
				ft_strdup("<<"))), *i += 2, HERE_DOC);
		else
			return (append_token(head, create_token(REDIRECT_IN, not_q, \
				ft_strdup("<"))), (*i)++, REDIRECT_IN);
	}
	else if (ft_isoper(cmd[*i]) == REDIRECT_OUT)
	{
		if (cmd[*i + 1] && ft_isoper(cmd[*i + 1]) == REDIRECT_OUT)
			return (append_token(head, create_token(REDIRECT_APPEND, not_q, \
				ft_strdup(">>"))), *i += 2, REDIRECT_APPEND);
		else
			return (append_token(head, create_token(REDIRECT_OUT, not_q, \
				ft_strdup(">"))), (*i)++, REDIRECT_OUT);
	}
	return (1);
}

int	handle_general(const char *cmd, int *i, t_state *s, t_token **head)
{
	while (ft_isspace(cmd[*i]))
		(*i)++;
	if (!cmd[*i])
		return (0);
	if (ft_isoper(cmd[*i]))
		return (handle_in_oper(cmd, i, head));
	else if (ft_isquote(cmd[*i]) == 1)
		return ((*i)++, *s = s_in_single_quote, 1);
	else if (ft_isquote(cmd[*i]) == 2)
		return ((*i)++, *s = s_in_double_quote, 2);
	else
		return (*s = s_in_word, 3);
}

int	handle_s_quote(const char *cmd, int *i, t_state *s, t_token **head)
{
	int		end_i;
	int		no_space;
	char	*val;

	end_i = *i;
	while (cmd[end_i] && ft_isquote(cmd[end_i]) != 1)
		end_i++;
	if (ft_isquote(cmd[end_i]) == 1)
	{
		val = ft_substr(cmd, *i, end_i - *i);
		if (val == NULL)
			return (ft_putstr_fd("handle_func/ft_substr() error\n", 2), ERR);
		no_space = !is_prev_space(cmd, *i);
		*i = end_i + 1;
		*s = s_in_general;
		if (!append_token(head, create_token(WORD, s_q, val)))
		{
			ft_free_lst(head);
			return (ERR);
		}
		last_token(*head)->no_space = no_space;
		return (1);
	}
	else
		return (ft_putstr_fd("minishell:single quote is unclosed\n", 2), ERR);
}

int	handle_d_quote(const char *cmd, int *i, t_state *s, t_token **head)
{
	int		end_i;
	int		no_space;
	char	*val;

	end_i = *i;
	while (cmd[end_i] && ft_isquote(cmd[end_i]) != 2)
		end_i++;
	if (ft_isquote(cmd[end_i]) == 2)
	{
		val = ft_substr(cmd, *i, end_i - *i);
		if (val == NULL)
			return (ft_putstr_fd("handle_func/ft_substr() error\n", 2), -1);
		no_space = !is_prev_space(cmd, *i);
		*i = end_i + 1;
		*s = s_in_general;
		if (!append_token(head, create_token(WORD, d_q, val)))
		{
			ft_free_lst(head);
			return (ERR);
		}
		last_token(*head)->no_space = no_space;
		return (1);
	}
	else
		return (ft_putstr_fd("minishell:double quote is unclosed\n", 2), ERR);
}

int	handle_in_word(const char *cmd, int *i, t_state *s, t_token **head)
{
	int		end_i;
	int		no_space;
	char	*val;

	end_i = *i;
	while (cmd[end_i] && !ft_isspace(cmd[end_i]) && \
		!ft_isoper(cmd[end_i]) && !ft_isquote(cmd[end_i]))
		end_i++;
	val = ft_substr(cmd, *i, end_i - *i);
	if (val == NULL)
		return (ft_putstr_fd("handle_func/ft_substr() error\n", 2), -1);
	no_space = !is_prev_space(cmd, *i);
	*i = end_i;
	*s = s_in_general;
	if (!append_token(head, create_token(WORD, not_q, val)))
	{
		ft_free_lst(head);
		return (ERR);
	}
	last_token(*head)->no_space = no_space;
	return (1);
}

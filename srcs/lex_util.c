/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:54:14 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/07 11:28:07 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char c);
int	ft_isoper(char c);
int	is_redirect(t_token_type type);

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

int	is_redirect(t_token_type type)
{
	if (type == REDIRECT_IN)
		return (1);
	else if (type == HERE_DOC)
		return (1);
	else if (type == REDIRECT_OUT)
		return (1);
	else if (type == REDIRECT_APPEND)
		return (1);
	else
		return (0);
}

int	is_prev_space(const char *cmd, int idx)
{
	int	i;

	i = idx - 1;
	while (i >= 0 && ft_isspace(cmd[i]))
		i--;
	if (i < idx - 1)
		return (1);
	return (0);
}

char	*combine_filename_tokens(t_token **cur_ptr)
{
	t_token	*cur;
	char	*filename;
	char	*temp;

	cur = *cur_ptr;
	filename = ft_strdup("");
	if (!filename)
		return (NULL);
	while (cur && cur->no_space == 1 && cur->type == WORD)
	{
		temp = ft_strdup(cur->val);
		if (!temp)
			return (free(filename), NULL);
		filename = ft_strjoin_free(filename, temp);
		if (!filename)
			return (NULL);
		cur = cur->next;
	}
	*cur_ptr = cur;
	return (filename);
}

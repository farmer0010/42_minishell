/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:48:02 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/30 10:58:50 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(const char *token_value);
char	*get_env_name_len(const char *val, int *env_len);
char	*expand_str(const char *val);

t_cmd	*get_cmd_info(t_token **head)
{
	t_cmd	*head_cmd;

	if (valid_syntax(head) != 0)
		return (ft_free_lst(head), NULL);
	head_cmd = get_cmd_list(head);
	if (!head_cmd)
	{
		ft_free_lst(head);
		return (ft_putstr_fd("get_cmd_list() fail\n", 2), NULL);
	}
	return (head_cmd);
}

t_cmd	*parse_cmd_line(const char *cmd)
{
	t_token	*token_head;
	t_cmd	*t_cmd_head;

	if (!cmd)
		return (NULL);
	token_head = NULL;
	t_cmd_head = NULL;
	get_token_info(cmd, &token_head);
	if (token_head == NULL)
		return (NULL);
	t_cmd_head = get_cmd_list(&token_head);
	if (t_cmd_head == NULL)
		return (free_token_list(token_head), NULL);
	return (t_cmd_head);
}

void syntax_error(const char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
}

char	*get_env_name_len(const char *val, int *env_len)
{
	char	*env_name;
	int		i;

	if (!val || !*val)
		return (NULL);
	*env_len = 0;
	if (val[0] == '?')
		return (*env_len = 1, ft_strdup("?"));
	i = 0;
	if (ft_isalpha(val[i]) || val[i] == '_')
	{
		i++;
		while (val[i] && (ft_isalnum(val[i]) || val[i] == '_'))
			i++;
	}
	if (i == 0)
		return (*env_len = 0, ft_strdup(""));
	env_name = ft_substr(val, 0, i);
	if (!env_name)
		return (NULL);
	return (*env_len = i, env_name);
}

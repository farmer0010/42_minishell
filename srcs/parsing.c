/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:48:02 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/28 13:43:40 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash
// bash의 구문 오류 종료 코드는 2

int		parse_input(t_token **head, t_cmd **cmd_lst);
static void syntax_error(const char *token_value);
char	*get_env_name_len(char *val, int *env_len);
char	*expand_str(const char *val);
int		here_doc(char *end);

static void syntax_error(const char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
}

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

char	*get_env_name_len(char *val, int *env_len)
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

char	*expand_str(const char *val)
{
	char	*expanded;
	char	*cur_remain[2];
	// 0 = current position in origin str, 1 = remain
	char	*doller_pos;
	char	*env[2];
	// 0 = env_name, 1 = env_value
	int		env_len;

	if (!val)
		return (NULL);
	cur_remain[0] = val;
	expanded = ft_strdup("");
	while (*cur_remain[0])
	{
		doller_pos = ft_strchr(cur_remain[0], '$');
		if (!doller_pos)
		{
			cur_remain[1] = ft_strdup(cur_remain[0]);
			if (!cur_remain[1])
				return (free(expanded), NULL);
			expanded = ft_strjoin_free(expanded, cur_remain[1]);
			if (!expanded)
				return (NULL);
			break ;
		}
		if (doller_pos > cur_remain[0])
		{
			cur_remain[1] = ft_substr(cur_remain[0], 0, doller_pos - cur_remain[0]);
			if (!cur_remain[1])
				return (free(expanded), NULL);
			expanded = ft_strjoin_free(expanded, cur_remain[1]);
			if (!expanded)
				return (NULL);
		}
		cur_remain[0] = doller_pos + 1;
		env[0] = get_env_name_len(cur_remain[0], &env_len);
		if (!env[0])
			return (free(expanded), NULL);
		if (env[0][0] == '?')
			env[1] = ft_itoa(g_exit_status);
		else
			env[1] = ft_strdup(getenv(env[0]));
		free(env[0]);
		if (env[1])
		{
			expanded = ft_strjoin_free(expanded, ft_strdup(env[1]));
			if (!expanded)
				return (NULL);
		}
		else
		{
			expanded = ft_strjoin_free(expanded, NULL);
			if (!expanded)
				return (NULL);
		}
		cur_remain[0] += env_len;
	}
	return (expanded);
}



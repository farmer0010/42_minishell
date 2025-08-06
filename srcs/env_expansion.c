/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:30:46 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/05 15:30:05 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(const char *val, t_shell_data *data);
char	*end_expansion(char *expanded, char *cur);
char	*append_pre_doller(char *expanded, const char *pos, const char *cur);
char	*process_expansion(const char *cur, char *expanded, int *env_len, \
	t_shell_data *data);
char	*plus_doller_sign(char *expanded, int *env_len);

char	*expand_str(const char *val, t_shell_data *data)
{
	char	*expanded;
	char	*cur;
	char	*doller_pos;
	int		env_len;

	if (!val)
		return (NULL);
	cur = (char *)val;
	expanded = ft_strdup("");
	while (*cur)
	{
		doller_pos = ft_strchr(cur, '$');
		if (!doller_pos)
		{
			expanded = end_expansion(expanded, ft_strdup(cur));
			break ;
		}
		if (doller_pos > cur)
			expanded = append_pre_doller(expanded, doller_pos, cur);
		cur = doller_pos + 1;
		expanded = process_expansion(cur, expanded, &env_len, data);
		cur += env_len;
	}
	return (expanded);
}

char	*plus_doller_sign(char *expanded, int *env_len)
{
	*env_len = 0;
	expanded = ft_strjoin_free(expanded, ft_strdup("$"));
	return (expanded);
}

char	*end_expansion(char *expanded, char *cur)
{
	expanded = ft_strjoin_free(expanded, cur);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*append_pre_doller(char *expanded, const char *pos, const char *cur)
{
	char	*before_doller;

	if (!cur || !*cur)
		return (expanded);
	before_doller = ft_substr(cur, 0, pos - cur);
	if (!before_doller)
		return (free(expanded), NULL);
	expanded = ft_strjoin_free(expanded, before_doller);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*process_expansion(const char *cur, char *expanded, int *env_len, \
	t_shell_data *data)
{
	char	*env_name;
	char	*env_value;

	if (!cur || !expanded)
		return (NULL);
	if (*cur == '\0' || !ft_isalpha(*cur))
		return (plus_doller_sign(expanded, env_len));
	env_name = get_env_name_len(cur, env_len);
	if (!env_name)
		return (free(expanded), NULL);
	if (env_name[0] == '?')
		env_value = ft_itoa(g_exit_status);
	else
		env_value = ft_strdup(get_env_value(data->env_list, env_name));
	free(env_name);
	if (env_value)
	{
		expanded = ft_strjoin_free(expanded, env_value);
		if (!expanded)
			return (NULL);
	}
	else
		return (expanded);
	return (expanded);
}

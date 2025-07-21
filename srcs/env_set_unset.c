/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:21:26 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 14:21:29 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env_value(t_list **env_list, const char *key)
{
	t_list	*cur;
	t_list	*prev;
	t_env	*env;

	cur = *env_list;
	prev = NULL;
	while (cur)
	{
		env = (t_env *)cur->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env_list = cur->next;
			free(env->key);
			free(env->value);
			free(env);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

int	set_env_value(t_list **env_list, const char *key, const char *value)
{
	t_env	*env;
	t_list	*cur;

	cur = *env_list;
	while (cur)
	{
		env = (t_env *)cur->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (0);
		}
		cur = cur->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (0);
}

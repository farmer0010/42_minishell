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

void	free_env_content(void *content)
{
	t_env	*env;

	if (content == NULL)
		return ;
	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

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
			ft_lstdelone(cur, free_env_content);
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
	char	*old_value;
	t_list	*new_list_node;

	cur = *env_list;
	while (cur)
	{
		env = (t_env *)cur->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			old_value = env->value;
			env->value = ft_strdup(value);
			if (!env->value)
			{
				env->value = old_value;
				return (1);
			}
			if (old_value)
				free(old_value);
			return (0);
		}
		cur = cur->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->key = ft_strdup(key);
	if (!env->key)
	{
		free(env);
		return (1);
	}
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env->key);
		free(env);
		return (1);
	}
	new_list_node = ft_lstnew(env);
	if (!new_list_node)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (1);
	}
	ft_lstadd_back(env_list, new_list_node);
	return (0);
}


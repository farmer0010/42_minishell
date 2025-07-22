/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:57:34 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 10:57:36 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node_content(const char *key, const char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (NULL);
	}
	return (env);
}

void	free_env_node(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

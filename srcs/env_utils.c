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

static t_env	*create_env_node_content(const char *key, const char *value)
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

t_list	*init_env_list(char **envp_sys)
{
	t_list	*env_list;
	t_env	*env_content;
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp_sys[i])
	{
		equal_sign = ft_strchr(envp_sys[i], '=');
		if (equal_sign)
		{
			key = ft_substr(envp_sys[i], 0, equal_sign - envp_sys[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(envp_sys[i]);
			value = ft_strdup("");
		}
		if (!key || !value)
		{
			free(key);
			free(value);
			ft_lstclear(&env_list, free_env_node);
			perror("minishell: malloc failed for env_list initialization");
			exit(EXIT_FAILURE);
		}
		env_content = create_env_node_content(key, value);
		free(key);
		free(value);
		if (!env_content)
		{
			ft_lstclear(&env_list, free_env_node);
			perror("minishell: malloc failed for env_content");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&env_list, ft_lstnew(env_content));
		i++;
	}
	return (env_list);
}


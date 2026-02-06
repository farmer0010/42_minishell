/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:25:53 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 14:25:56 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_env_key_value(const char *env_str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		*key = ft_substr(env_str, 0, equal_sign - env_str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(env_str);
		*value = ft_strdup("");
	}
	if (!*key || !*value)
		return (0);
	return (1);
}

static void	create_and_add_env(t_list **env_list, char *key, char *value)
{
	t_env	*env_content;
	t_list	*new_node;

	env_content = create_env_node_content(key, value);
	free(key);
	free(value);
	if (!env_content)
	{
		ft_lstclear(env_list, free_env_node);
		perror("minishell: malloc failed for env_content");
		exit(EXIT_FAILURE);
	}
	new_node = ft_lstnew(env_content);
	if (!new_node)
	{
		free_env_node(env_content);
		ft_lstclear(env_list, free_env_node);
		perror("minishell: malloc failed for env_list node");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(env_list, new_node);
}

t_list	*init_env_list(char **envp_sys)
{
	t_list	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp_sys[i])
	{
		if (!extract_env_key_value(envp_sys[i], &key, &value))
		{
			free(key);
			free(value);
			ft_lstclear(&env_list, free_env_node);
			perror("minishell: malloc failed for env_list initialization");
			exit(EXIT_FAILURE);
		}
		create_and_add_env(&env_list, key, value);
		i++;
	}
	return (env_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:59:32 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/21 10:59:34 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_list *env_list, const char *key)
{
	t_list	*current;
	t_env	*env;

	if (!env_list || !key)
		return (NULL);
	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		current = current->next;
	}
	return (NULL);
}

static t_env	*get_env_node(t_list *env_list, const char *key)
{
	t_list	*current;
	t_env	*env;

	if (!env_list || !key)
		return (NULL);
	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		current = current->next;
	}
	return (NULL);
}

int	set_env_value(t_list **env_list, const char *key, const char *value)
{
	t_env	*env;
	char	*new_value;

	if (!key || !is_valid_identifier(key))
	{
		errno = EINVAL;
		return (-1);
	}
	env = get_env_node(*env_list, key);
	if (env)
	{
		if (value && ft_strlen(value) == 0
			&& env->value && ft_strlen(env->value) > 0)
			return (0);
		new_value = ft_strdup(value);
		if (!new_value)
			return (-1);
		free(env->value);
		env->value = new_value;
		return (0);
	}
	env = create_env_node_content(key, value);
	if (!env)
		return (-1);
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (0);
}

int	unset_env_value(t_list **env_list, const char *key)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;

	if (!key || !is_valid_identifier(key) || ft_strchr(key, '='))
	{
		errno = EINVAL;
		return (-1);
	}
	current = *env_list;
	prev = NULL;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			ft_lstdelone(current, free_env_node);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

char	**convert_env_list_to_array(t_list *env_list)
{
	char	**env_array;
	t_list	*current;
	t_env	*env_content;
	int		len;
	int		i;

	len = ft_lstsize(env_list);
	env_array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_array)
	{
		perror("minishell: malloc failed for env_array");
		return (NULL);
	}
	i = 0;
	current = env_list;
	while (current)
	{
		env_content = (t_env *)current->content;
		env_array[i] = ft_strjoin_three(env_content->key, "=",
				env_content->value);
		if (!env_array[i])
		{
			while (i-- > 0)
				free(env_array[i]);
			free(env_array);
			perror("minishell: malloc failed for env_array string");
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env_array(char **env_array)
{
	free_argv(env_array);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:56:23 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/10 10:56:24 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_env_from_list(t_list *env_list)
{
	return (get_env_value(env_list, "PATH"));
}

static char	**get_paths(t_list *env_list)
{
	char	*path_env;

	path_env = get_path_env_from_list(env_list);
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

static char	*search_path(char **paths, char *cmd_name)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd_name);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd_name, t_list *env_list)
{
	char	**paths;
	char	*exec_path;

	if (!cmd_name || ft_strlen(cmd_name) == 0)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	paths = get_paths(env_list);
	if (!paths)
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	exec_path = search_path(paths, cmd_name);
	free_argv(paths);
	return (exec_path);
}

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

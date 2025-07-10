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

#include "../includes/minishell.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**get_paths(char **envp)
{
	char	*path_env;
	char	**paths;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

static char	*search_path(char **paths, char *cmd_name)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
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

char	*find_executable(char *cmd_name, char **envp)
{
	char	**paths;
	char	*exec_path;

	paths = get_paths(envp);
	if (!paths)
		return (NULL);
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

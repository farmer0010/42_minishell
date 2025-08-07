/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:56:32 by juyoukim          #+#    #+#             */
/*   Updated: 2025/08/07 11:16:20 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipefd, int count)
{
	int	i;

	if (!pipefd)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

static void	free_resources(t_shell_data *data)
{
	if (data->cmd_list)
	{
		free_cmd_list(data->cmd_list);
		data->cmd_list = NULL;
	}
	if (data->token_list)
	{
		free_token_list(data->token_list);
		data->token_list = NULL;
	}
	if (data->env_list)
	{
		ft_lstclear(&(data->env_list), free_env_node);
		data->env_list = NULL;
	}
	if (data->pipe_data.pipefd)
	{
		free_pipes(data->pipe_data.pipefd, data->pipe_data.count - 1);
		data->pipe_data.pipefd = NULL;
	}
}

static void	close_backups(t_shell_data *data)
{
	if (data->stdin_backup != -1)
	{
		close(data->stdin_backup);
		data->stdin_backup = -1;
	}
	if (data->stdout_backup != -1)
	{
		close(data->stdout_backup);
		data->stdout_backup = -1;
	}
}

void	free_all(t_shell_data *data)
{
	if (!data)
		return ;
	free_resources(data);
	close_backups(data);
}

int	token_error_handler(t_token *new_token, char *val, t_token **head)
{
	if (!new_token)
	{
		free(val);
		ft_free_lst(head);
		return (-1);
	}
	if (!append_token(head, new_token))
	{
		free_token_node(new_token);
		ft_free_lst(head);
		return (-1);
	}
	return (1);
}

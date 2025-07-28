/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:26:31 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/28 13:45:37 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_node(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	t_token	*cur;
	int		argv_len;
	int		i;

	if (!start)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->temp_file = NULL;
	if (get_argv_set_fd(cmd, start, &argv_len) < 0)
		return (free(cmd), NULL);
	cur = start;
	cmd->argv = malloc(sizeof(char *) * (argv_len + 1));
	if (!cmd->argv)
	{
		if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
			close(cmd->outfile);
		return (free(cmd), NULL);
	}
	i = 0;
	cur = start;
	while (cur && cur != end->next)
	{
		if (is_redirect(cur->type))
		{
			cur = cur->next->next;
			continue ;
		}
		if (cur->quote_status == s_q)
			cmd->argv[i] = ft_strdup(cur->val);
		else
			cmd->argv[i] = expand_str(cur->val);
		i++;
		cur = cur->next;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}

t_cmd	*get_cmd_list(t_token **head)
{
	t_token *cur;
	t_token *block_start;
	t_cmd *head_cmd;
	t_cmd *new_cmd;

	if (!head || !*head)
		return (NULL);
	cur = *head;
	block_start = *head;
	head_cmd = NULL;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			new_cmd = create_cmd_node(block_start, cur->prev);
			if (!new_cmd)
			{
				ft_free_cmd_list(head_cmd);
				return (ft_putstr_fd("create_cmd() fail\n", 2), NULL);
			}
			block_start = cur->next;
			if (append_cmd(&head_cmd, new_cmd) < 0)
			{
				ft_putstr_fd("append_cmd() fail\n", 2);
				return (ft_free_cmd_list(head_cmd), NULL);
			}
		}
		cur = cur->next;
	}
	if (block_start)
	{
		new_cmd = create_cmd_node(block_start, get_last_cmd(head_cmd));
		if (!new_cmd)
		{
			ft_free_cmd_list(head_cmd);
			return (ft_putstr_fd("create_cmd() fail\n", 2), NULL);
		}
		if (append_cmd(&head_cmd, new_cmd) < 0)
		{
			ft_putstr_fd("append_cmd() fail\n", 2);
			return (ft_free_cmd_list(head_cmd), NULL);
		}
	}
	return (head_cmd);
}

int	append_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*cur;

	if (!head || !cmd)
	{
		printf("list_func.c/append_cmd error\n");
		return (-1);
	}
	if (!*head)
	{
		*head = cmd;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = cmd;
	return (1);
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	t_cmd	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

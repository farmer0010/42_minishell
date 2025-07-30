/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:26:31 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/30 12:25:37 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmd_list(t_token **head, t_shell_data *data);
t_cmd	*create_cmd_node(t_token *start, t_token *end, t_shell_data *data);
int		append_cmd(t_cmd **head, t_cmd *cmd);
int		create_append_cmd(t_cmd **head, t_token *start, t_token *end, \
	t_shell_data *data);
t_cmd	*create_init_cmd(t_token *start, t_token *end);

t_cmd	*get_cmd_list(t_token **head, t_shell_data *data)
{
	t_token	*cur;
	t_token	*start;
	t_cmd	*head_cmd;

	if (!head || !*head)
		return (NULL);
	cur = *head;
	start = *head;
	head_cmd = NULL;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (create_append_cmd(&head_cmd, start, cur->prev, data) < 0)
				return (free_cmd_list(head_cmd), NULL);
			start = cur->next;
		}
		cur = cur->next;
	}
	if (start)
	{
		if (create_append_cmd(&head_cmd, start, last_token(start), data) < 0)
			return (free_cmd_list(head_cmd), NULL);
	}
	return (head_cmd);
}

t_cmd	*create_cmd_node(t_token *start, t_token *end, t_shell_data *data)
{
	t_cmd	*cmd;
	t_token	*cur;
	int		i;

	if (!start || !end)
		return (NULL);
	cmd = create_init_cmd(start, end);
	if (!cmd)
		return (NULL);
	i = 0;
	cur = start;
	while (cur && cur != end->next)
	{
		if (is_redirect(cur->type))
		{
			cur = cur->next->next;
			continue ;
		}
		if (set_argv_val(cmd, cur, i, data) < 0)
			return (free_cmd_node(cmd), NULL);
		i++;
		cur = cur->next;
	}
	return (cmd);
}

int	append_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*cur;

	if (!head || !cmd)
	{
		ft_putstr_fd("list_func.c/append_cmd error\n", 2);
		return (-1);
	}
	if (!*head)
	{
		*head = cmd;
		return (1);
	}
	cur = get_last_cmd(*head);
	if (!cur)
		return (-1);
	cur->next = cmd;
	return (1);
}

int	create_append_cmd(t_cmd **head, t_token *start, t_token *end, \
	t_shell_data *data)
{
	t_cmd	*new_cmd;

	if (!head || !start)
		return (-1);
	new_cmd = create_cmd_node(start, end, data);
	if (!new_cmd)
		return (perror("malloc failed in create_append_cmd()\n"), -1);
	if (append_cmd(head, new_cmd) < 0)
	{
		free_cmd_node(new_cmd);
		return (-1);
	}
	return (1);
}

t_cmd	*create_init_cmd(t_token *start, t_token *end)
{
	t_cmd	*new_cmd;
	int		argv_len;

	if (!start)
		return (NULL);
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->infile = STDIN_FILENO;
	new_cmd->outfile = STDOUT_FILENO;
	if (get_argv_set_fd(new_cmd, start, end, &argv_len) < 0)
		return (free_cmd_node(new_cmd), NULL);
	new_cmd->argv = ft_calloc((argv_len + 1), sizeof(char *));
	if (!new_cmd->argv)
		return (free_cmd_node(new_cmd), NULL);
	return (new_cmd);
}

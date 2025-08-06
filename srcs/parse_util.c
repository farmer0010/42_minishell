/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:37:01 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/06 17:38:07 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		valid_syntax(t_token **head);
int		get_argv_set_fd(t_cmd *cmd, t_token *start, t_token *end, \
	int *argv_len);
int		set_argv_val(t_cmd *cmd, t_token *cur, int *idx, t_shell_data *data);
int		set_fd(t_token *cur, t_cmd *cmd, char *filename);

int	valid_syntax(t_token **head)
{
	t_token	*cur;

	if (!head || !*head)
		return (0);
	cur = *head;
	if (cur->type == PIPE)
		return (syntax_error(cur->val), 2);
	while (cur)
	{
		if (cur->next != NULL)
		{
			if (cur->type == PIPE && cur->next->type == PIPE)
				return (syntax_error(cur->next->val), 2);
			else if (is_redirect(cur->type) && \
						cur->next->type != WORD)
				return (syntax_error(cur->next->val), 2);
		}
		else
		{
			if (is_redirect(cur->type) || cur->type == PIPE)
				return (syntax_error("newline"), 2);
		}
		cur = cur->next;
	}
	return (0);
}

char	*combine_filename_tokens(t_token **cur_ptr)
{
	t_token	*cur;
	char	*filename;
	char	*temp;

	cur = *cur_ptr;
	filename = ft_strdup("");
	if (!filename)
		return (NULL);
	while (cur && cur->no_space == 1 && cur->type == WORD)
	{
		temp = ft_strdup(cur->val);
		if (!temp)
			return (free(filename), NULL);
		filename = ft_strjoin_free(filename, temp);
		if (!filename)
			return (NULL);
		cur = cur->next;
	}
	*cur_ptr = cur;
	return (filename);
}

int	get_argv_set_fd(t_cmd *cmd, t_token *start, t_token *end, int *argv_len)
{
	t_token	*cur;
	char	*filename;

	cur = start;
	while (cur && cur != end->next)
	{
		if (is_redirect(cur->type))
		{
			filename = combine_filename_tokens(&cur->next);
			if (!filename)
				return (-1);
			set_fd(cur, cmd, filename);
			free(filename);
		}
		else if (cur->type == WORD)
			(*argv_len)++;
		cur = cur->next;
	}
	return (1);
}

int	set_argv_val(t_cmd *cmd, t_token *cur, int *idx, t_shell_data *data)
{
	char	*expanded;

	if (!cmd || !cur)
		return (-1);
	if (cmd->redirect_error == 1)
		return (1);
	if (cur->quote_status == s_q)
		expanded = ft_strdup(cur->val);
	else
		expanded = expand_str(cur->val, data);
	if (!expanded)
	{
		free_cmd_node(cmd);
		return (perror("malloc failed in set_argv_val()\n"),
			g_exit_status = 1, -1);
	}
	if (*idx > 0 && cur->prev && cur->prev->type == WORD && cur->no_space == 1)
		cmd->argv[*idx - 1] = ft_strjoin_free(cmd->argv[*idx - 1], expanded);
	else
	{
		cmd->argv[*idx] = expanded;
		(*idx)++;
	}
	return (1);
}

static void	check_filepath_infile_fd(t_cmd *cmd)
{
	if (cmd->filepath != NULL)
	{
		unlink(cmd->filepath);
		free(cmd->filepath);
		cmd->filepath = NULL;
	}
	if (cmd->infile > 2)
		close(cmd->infile);
}

int	set_fd(t_token *cur, t_cmd *cmd, char *filename)
{
	if (!cur || !cmd)
		return (-1);
	if (cur->type == REDIRECT_IN || cur->type == HERE_DOC)
	{
		check_filepath_infile_fd(cmd);
		if (cur->type == REDIRECT_IN)
			cmd->infile = open(filename, O_RDONLY);
		else if (cur->type == HERE_DOC)
			cmd->infile = here_doc(filename, &cmd->filepath);
	}
	else if (cur->type == REDIRECT_OUT || cur->type == REDIRECT_APPEND)
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		if (cur->type == REDIRECT_OUT)
			cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, \
				0644);
		else if (cur->type == REDIRECT_APPEND)
			cmd->outfile = open(filename, O_CREAT | O_WRONLY | \
				O_APPEND, 0644);
	}
	if (cmd->infile < 0 || cmd->outfile < 0)
		case_invalid_fd(cmd, filename);
	return (1);
}

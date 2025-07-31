/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:12:15 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/11 09:12:17 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirects(t_cmd *cmd)
{
	if (cmd->infile != -1 && cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 (infile) failed");
			close(cmd->infile);
			return (1);
		}
		close(cmd->infile);
	}
	if (cmd->outfile != -1 && cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 (outfile) failed");
			close(cmd->outfile);
			return (1);
		}
		close(cmd->outfile);
	}
	return (0);
}

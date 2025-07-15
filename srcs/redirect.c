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

#include "../includes/minishell.h"

int	handle_redirect_in(t_cmd *cmd)
{
	if (cmd -> infile != -1)
	{
		if (dup2(cmd -> infile, STDIN_FILENO) == -1)
		{
			perror("dup2 (infile)");
			return (1);
		}
		close(cmd -> infile);
	}
	return (0);
}

int	handle_redirect_out(t_cmd *cmd)
{
	if (cmd -> outfile != -1)
	{
		if (dup2(cmd -> outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 (outfile)");
			return (1);
		}
		close(cmd -> outfile);
	}
	return (0);
}

int	handle_redirects(t_cmd *cmd)
{
	if (handle_redirect_in(cmd) || handle_redirect_out(cmd))
		return (1);
	return (0);
}

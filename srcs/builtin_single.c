/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:27:04 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/13 16:27:05 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_builtin(t_cmd *cmd)
{
	if (!cmd || cmd->next)
		return (FALSE);
	return (is_builtin(cmd->argv[0]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:32:13 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/11 01:51:03 by gimtaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexing(const char *cmd)
{
	t_state cur_state = s_in_general;
	t_token_type token_type;
	char *token_value;
}

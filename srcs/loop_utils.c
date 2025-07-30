/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:16:18 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/30 10:16:19 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_user_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && *input)
		add_history(input);
	return (input);
}

int	perform_lexing(t_shell_data *data, char *input)
{
	data->token_list = NULL;
	get_token_info(input, &(data->token_list));
	free(input);
	if (!data->token_list)
		return (0);
	return (1);
}

int	perform_parsing(t_shell_data *data)
{
	data->cmd_list = get_cmd_info(&(data->token_list));
	data->token_list = NULL;
	if (!data->cmd_list)
		return (0);
	return (1);
}

void	cleanup_cmd_data(t_shell_data *data)
{
	if (data->cmd_list)
	{
		free_cmd_list(data->cmd_list);
		data->cmd_list = NULL;
	}
	data->token_list = NULL;
}

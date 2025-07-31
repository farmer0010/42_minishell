/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:16:18 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/31 11:02:56 by taewonki         ###   ########.fr       */
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
	data->cmd_list = get_cmd_info(&(data->token_list), data);
	data->token_list = NULL;
	if (! data->cmd_list)
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

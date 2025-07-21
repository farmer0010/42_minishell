/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:09:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/17 11:09:36 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:09:30 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/17 11:09:36 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_shell_data *data)
{
	char	*input;

	while (TRUE)
	{
		init_signal();
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);

		// 실제 구현 시 파서 함수 호출 필요
		// data->cmd_list = parse(input);

		// 임시로 더미 명령 생성 함수 호출
		data->cmd_list = make_fake_cmd();

		if (data->cmd_list)
			execute_cmds(data);

		free(input);

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
	}
}


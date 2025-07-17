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

#include "minishell.h"

void	start_minishell(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (! input)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*input)
			add_history(input);
		printf("입력한 명령어: %s\n", input);  // 나중엔 파서로 교체
		free(input);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:25:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/10 15:49:25 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("minishell> ");
		if (!cmd)
		{
			ft_printf("readline() error\n");
			break ;
		}
		if (*cmd == '\0')
		{
			free(cmd);
			continue;
		}
		add_history(cmd); // readline()으로 입력받은 값을 히스토리에 추가
		// cmd 문자열 파싱 + 실행 로직 구성

		free(cmd);
		cmd = NULL;
		// 받은 문자열을 다 사용했으면 free해주고 NULL 초기화해서 다음 명령 받을 준비
	}
}

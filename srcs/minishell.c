/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimtaewon <gimtaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:25:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/11 13:15:18 by gimtaewon        ###   ########.fr       */
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
			// 아무것도 입력 안하고 엔터를 누른 경우 => 빈 문자열
			free(cmd);
			// 해제하고
			continue;
			//다시 입력받기
		}
		add_history(cmd); // readline()으로 입력받은 값을 히스토리에 추가
		// cmd 문자열 파싱 + 실행 로직 구성
		// 여기서 cmd를 파싱하고 실행하는 로직을 구현.
		free(cmd);
		// 작업 다 끝나면 free
		cmd = NULL;
		// 받은 문자열을 다 사용했으면 free해주고 NULL 초기화해서 다음 명령 받을 준비
	}
}

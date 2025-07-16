/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:21:02 by gimtaewon         #+#    #+#             */
/*   Updated: 2025/07/16 13:57:31 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	get_token_info(const char *cmd, t_node **head)
{
	t_state	state;
	char	*token_val;
	int		i;
	int		token_start_i = 0;
	int		token_end_i = 0;

	i = 0;
	state = s_in_general;
	while (cmd[i])
	{
		if (state == s_in_general)
		// 평상시 상태일때
		{
			while (ft_isspace(cmd[i]))
				i++;
			if (!cmd[i])
				break ;
			// 시작 공백 건너뛰기
			token_start_i = i;
			// 토큰 시작 문자열 지정
			if (ft_isoper(cmd[i]))
			{
				if (ft_isoper(cmd[i]) == PIPE)
				// 다음 문자가 "|" 일때
				{
					append_token(head, create_node(PIPE, "|"));
					i++;
					continue ;
				}
				// 공백 건너뛰고 나온 문자가 '|' 라면 바로 노드 만들어서 이어붙여주고 i++
				// 그 후 continue해서 처음으로 돌아가서 분기 진행할수 있도록 함
				// ||는 보너스라서 일단 보류
				else if (ft_isoper(cmd[i]) == REDIRECT_IN)
				//
				{
					if (cmd[i + 1] == '<')
					{
						append_token(head, create_node(HERE_DOC, "<<"));
						i += 2;
					}
					else
					{
						append_token(head, create_node(REDIRECT_IN, "<"));
						i++;
					}
					continue ;
				}
				else if (ft_isoper(cmd[i]) == REDIRECT_OUT)
				{
					if (cmd[i + 1] == ">")
					{
						append_token(head, create_node(REDIRECT_APPEND, ">>"));
						i += 2;
					}
					else
					{
						append_token(head, create_node(REDIRECT_OUT, ">"));
						i++;
					}
					continue ;
				}
				// | < << > >> 인 경우 분기인데, 나중에 & 추가할거면 그때 추가
			}
			else if (ft_isquote(cmd[i]) == 1)
			{
				i++;
				token_start_i = i;
				state = s_in_single_quote;
				continue;
			}
			else if (ft_isquote(cmd[i]) == 2)
			{
				i++;
				token_start_i = i;
				state = s_in_double_quote;
				continue;
			}
			else
			{
				state = s_in_word;
				continue;
			}
		}
		else if (state == s_in_single_quote)
		// ' 인 경우 분기점
		// 현재 상태
		// : 'ls ...' 일때 ' 하나를 건너뛰고 (위의 s_in_general분기문에서)
		// : ls ... ' 이 상태
		// 1. 메타문자 해석 없이 모든 문자 리터럴 처리
		// 2. 따옴표가 닫히지 않았을 경우 에러 처리
		{
			token_end_i = i;
			while (cmd[token_end_i] && ft_isquote(cmd[token_end_i]) != 1)
				token_end_i++;
			// cmd가 null이 아니고, '이 안나올 동안 계속 인덱스 증가
			if (ft_isquote(cmd[token_end_i]) == 1)
			// ' 닫는 따옴표를 만나면?
			{
				token_val = ft_substr(cmd, token_start_i, token_end_i - token_start_i);
				append_token(head, create_node(WORD, token_val));
				i = token_end_i + 1;
				state = s_in_general;
			}
			else
			// 근데 다 끝나고 나왔는데 널이다? => 닫는 따옴표가 없다! = 오류처리
			{
				printf("unclosed single quote!\n");
				// 대충 모든 노드 헤제하고 exit하는 함수
				return ;
			}
			continue ;
		}
		else if (state == s_in_double_quote)
		// "" 인 경우 분기점
		// 1. 메타문자는 \(이스케이프), $ (변수 확장) 같은 이런것들 포함
		// 2. 얘도 따옴표 닫히지 않았을때 에러처리
		{
			token_end_i = i;
			while (cmd[token_end_i] && ft_isquote(cmd[token_end_i]) != 2)
				token_end_i++;
			// cmd가 null이 아니고, "이 안나올 동안 계속 인덱스 증가
			if (ft_isquote(cmd[token_end_i]) == 2)
			// ' 닫는 따옴표를 만나면?
			{
				token_val = ft_substr(cmd, token_start_i, token_end_i - token_start_i);
				append_token(head, create_node(WORD, token_val));
				i == token_end_i + 1;
				state = s_in_general;
			}
			else
			// 근데 다 끝나고 나왔는데 널이다? => 닫는 따옴표가 없다! = 오류처리
			{
				printf("unclosed double quote!\n");
				// 대충 모든 노드 해제하고 exit하는 함수
				return ;
			}
			continue;
		}
		else if (state == s_in_word)
		// 일반적인 단어 안에 있을 때, 보통의 경우 공백이 나오면 단어 하나를 끝낸다.
		{
			token_end_i = i;
			while (!ft_isspace(cmd[token_end_i]) && !ft_isoper(cmd[token_end_i]) && !ft_isquote(cmd[token_end_i]))
				token_end_i++;
			token_val = ft_substr(cmd, token_start_i, token_end_i - token_start_i);
			append_token(head, create_node(WORD, token_val));
			i = token_end_i;
			state = s_in_general;
			continue;
		}
	}
	if (state == s_in_word)
	{
		token_val = ft_substr(cmd, token_start_i, i - token_start_i);
		append_token(head, create_node(WORD, token_val));
	}
}

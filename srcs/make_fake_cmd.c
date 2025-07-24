/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fake_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:20:55 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/10 09:20:57 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 이 함수는 파서가 구현되면 삭제될 임시 함수입니다.
t_cmd   *make_fake_cmd(void)
{
    t_cmd   *cmd1;
    t_cmd   *cmd2;
    t_cmd   *cmd3;

    cmd1 = malloc(sizeof(t_cmd));
    cmd2 = malloc(sizeof(t_cmd));
    cmd3 = malloc(sizeof(t_cmd));
    if (!cmd1 || !cmd2 || !cmd3)
    {
        if (cmd1)
            free(cmd1);
        if (cmd2)
            free(cmd2);
        if (cmd3)
            free(cmd3);
        perror("minishell: make_fake_cmd: malloc failed");
        return (NULL);
    }
    cmd1->argv = ft_split("ls -l", ' ');
    cmd1->infile = -1;
    cmd1->outfile = -1;
    cmd1->next = cmd2;
    if (!cmd1->argv)
    {
        free(cmd1);
        free(cmd2);
        free(cmd3);
        return (NULL);
    }
    cmd2->argv = ft_split("echo hello", ' ');
    cmd2->infile = -1;
    cmd2->outfile = -1;
    cmd2->next = cmd3;
    if (!cmd2->argv)
    {
        free_argv(cmd1->argv);
        free(cmd1);
        free(cmd2);
        free(cmd3);
        return (NULL);
    }
    cmd3->argv = ft_split("pwd", ' ');
    cmd3->infile = -1;
    cmd3->outfile = -1;
    cmd3->next = NULL;
    if (!cmd3->argv)
    {
        free_argv(cmd1->argv);
        free_argv(cmd2->argv);
        free(cmd1);
        free(cmd2);
        free(cmd3);
        return (NULL);
    }
    return (cmd1);
}


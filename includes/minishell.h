/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:33 by juyoukim          #+#    #+#             */
/*   Updated: 2025/07/09 13:44:43 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_cmd {
    char **argv;
    int infile;
    int outfile;
    int is_builtin;
    struct s_cmd *next;
} t_cmd;

void    execute_cmds(t_cmd *cmd);
char    *find_executable(char *cmd_name, char **envp);
char    *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
void    free_argv(char **argv);

#endif

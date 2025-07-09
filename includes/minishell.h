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
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

# define READ_END 0
# define WRITE_END 1
# define TRUE 1
# define FALSE 0

typedef struct s_cmd {
	char **argv;
	int infile;
	int outfile;
	int is_builtin;
	struct s_cmd *next;
} t_cmd;

void	execute_cmds(t_cmd *cmd);
t_cmd	*make_fake_cmd(void);
void	free_all(t_cmd *cmd, char *input);
void	free_argv(char **argv);

#endif

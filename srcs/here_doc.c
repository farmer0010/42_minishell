/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:31:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/08/04 15:15:45 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_newline_fd(char *line, int fd);
static char	*open_here_doc_file(int *fd);
int			here_doc(char *end, char **filepath);

static char	*open_here_doc_file(int *fd)
{
	static int	file_no;
	char		*filename;
	char		*num;

	num = ft_itoa(file_no++);
	if (!num)
		return (perror("malloc() fail\n"), NULL);
	filename = ft_strjoin(".heredoc_tmp", num);
	free(num);
	if (!filename)
		return (perror("malloc() fail\n"), NULL);
	*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("heredoc file open() fail\n");
		free(filename);
		return (NULL);
	}
	return (filename);
}

static void	write_newline_fd(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

int	here_doc(char *end, char **filepath)
{
	int		fd_write;
	char	*line;

	*filepath = open_here_doc_file(&fd_write);
	if (!*filepath || fd_write < 0)
		return (ft_putstr_fd("open() fail\n", 2), -1);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			unlink(*filepath);
			free(*filepath);
			*filepath = NULL;
			close(fd_write);
			signal(SIGINT, sigint_handler);
			return (-1);
		}
		if (!line)
		{
			if (g_exit_status == 130)
			{
				unlink(*filepath);
				free(*filepath);
				*filepath = NULL;
				close(fd_write);
				signal(SIGINT, sigint_handler);
				return (-1);
			}
			break ;
		}
		if (ft_strncmp(line, end, ft_strlen(end)) == 0 && \
				ft_strlen(line) == ft_strlen(end))
		{
			free(line);
			break ;
		}
		write_newline_fd(line, fd_write);
		free(line);
	}
	close(fd_write);
	signal(SIGINT, sigint_handler);
	return (open(*filepath, O_RDONLY));
}

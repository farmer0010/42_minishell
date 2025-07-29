/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:31:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/29 13:31:14 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *end, char **filepath);

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
	int		fd_read;
	char	*line;

	if (fd_write < 0 || !*filepath)
		return (ft_putstr_fd("open() fail\n", 2), -1);
	*filepath = open_here_doc_file(&fd_write);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
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
	fd_read = open(*filepath, O_RDONLY);
	return (fd_read);
}

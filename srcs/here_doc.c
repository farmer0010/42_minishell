/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:31:19 by taewonki          #+#    #+#             */
/*   Updated: 2025/07/28 13:48:12 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *end);

static int open_here_doc_file(void)
{
	static int	file_no;
	int 		fd;
	char		*filename;

	filename = ft_strjoin(".heredoc_tmp", ft_itoa(file_no++));
	if (!filename)
	{
		perror("malloc() fail\n");
		return (-1);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	if (fd < 0)
	{
		perror("heredoc file open() fail\n");
		return (-1);
	}
	return (fd);
}

int	here_doc(char *end)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("open() fail\n", 2), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, end, ft_strlen(end)) == 0 &&
				ft_strlen(line) == ft_strlen(end))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (fd);
}

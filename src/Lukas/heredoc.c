/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:06:59 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/18 15:17:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

static int	handle_heredoc_interrupt(char *line, int fd, t_shell *data)
{
	if (g_signal_status == SIGINT)
	{
		if (line)
			free(line);
		close(fd);
		data->last_exit = 130;
		g_signal_status = 0;
		return (-1);
	}
	return (0);
}

static int	safe_write(int fd, char *buf, size_t len, size_t *total)
{
	ssize_t	written;

	if (*total + len > HEREDOC_MAX_SIZE)
	{
		write(2, "minishell: heredoc too large\n", 29);
		return (-1);
	}
	written = write(fd, buf, len);
	if (written < 0)
		return (-1);
	*total += written;
	return (0);
}

static int	write_heredoc_line(int fd, char *line, size_t *total)
{
	if (safe_write(fd, line, ft_strlen(line), total) < 0)
		return (-1);
	if (safe_write(fd, "\n", 1, total) < 0)
		return (-1);
	return (0);
}

static int	fill_heredoc(int fd, t_redir *hd, t_shell *data)
{
	char	*line;
	size_t	total;

	total = 0;
	while (1)
	{
		line = read_heredoc_line();
		if (handle_heredoc_interrupt(line, fd, data) < 0)
			return (-1);
		if (!line)
			break ;
		if (is_delimiter(line, hd->file))
		{
			free(line);
			break ;
		}
		line = process_line(hd, data, line);
		if (write_heredoc_line(fd, line, &total) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	create_heredoc(t_redir *hd, t_shell *data)
{
	char	path[256];
	int		fd;

	fd = create_heredoc_tmpfile(path, hd->file);
	if (fd < 0)
	{
		perror("heredoc tmpfile");
		return (1);
	}
	hd->tmp_file = ft_strdup(path);
	if (!hd->tmp_file)
	{
		close (fd);
		return (1);
	}
	handle_signals_heredoc();
	if (fill_heredoc(fd, hd, data) < 0)
		return (-1);
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmpfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:01:44 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/06 12:19:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "miniheaven.h"

#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TMP_DIR
# define TMP_DIR "/tmp"
#endif

#ifndef MAX_ATTEMPTS
# define MAX_ATTEMPTS 1000
#endif

#define HEREDOC_MAX_SIZE (1024 * 1024)

static void	append_number(char *buf, size_t *j, long n)
{
	char	tmp[32];
	int		i;

	i = 0;
	if (n == 0)
		tmp[i++] = '0';
	else
	{
		while (n > 0)
		{
			tmp[i++] = '0' + (n % 10);
			n /= 10;
		}
	}
	while (i--)
		buf[(*j)++] = tmp[i];
}

static void	build_tmp_path(char *path, int counter)
{
	size_t	i;
	pid_t	pid;

	pid = getpid();
	strcpy(path, TMP_DIR "/.heredoc_");
	i = strlen(path);
	append_number(path, &i, (long)pid);
	path[i++] = '_';
	append_number(path, &i, (long)counter);
	path[i] = '\0';
}

int	create_heredoc_tmpfile(char *path_out)
{
	int	fd;
	int	attempt;

	attempt = 0;
	while (attempt < MAX_ATTEMPTS)
	{
		build_tmp_path(path_out, attempt);
		fd = open(path_out, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		attempt++;
	}
	return (-1);
}

static int	safe_write(int fd, char *buf, size_t len, size_t *total, int expand)
{
	ssize_t	written;
	char	*expanded;

	if (*total + len > HEREDOC_MAX_SIZE)
	{
		write(2, "minishell: heredoc too large\n", 29);
		return (-1);
	}
	if (expand)
	{
		expanded = expand_line(data, buf);
		free(buf);
		buf = expanded;
	}
	written = write(fd, buf, len);
	if (written < 0)
	{
		perror("write");
		return (-1);
	}
	*total += written;
	return (0);
}


int	create_heredoc(const char *delimiter)
{
	char	path[256];
	int		fd;
	char	*line;
	size_t	total_written;

	total_written = 0;
	fd = create_heredoc_tmpfile(path);
	if (fd < 0)
	{
		perror("tmpfile");
		return (1);
	}
	unlink(path);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (safe_write(fd, line, strlen(line), &total_written) < 0 || safe_write(fd, "\n", 1, &total_written) < 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	if (lseek(fd, 0, SEEK_SET) < 0)
	{
		perror("lseek");
		close (fd);
		return (-1);
	}
	return (fd);
}

int	main()
{
	create_heredoc("A");
	return (0);
}

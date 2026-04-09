/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmpfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:01:44 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 14:55:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"
extern volatile sig_atomic_t    g_signal_status;

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
	i = ft_strlen(path);
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
		fd = wopen(path_out, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		attempt++;
	}
	return (-1);
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
	{
		perror("write");
		return (-1);
	}
	*total += written;
	return (0);
}


int	create_heredoc(t_redir *hd, t_shell *data)
{
	char	path[256];
	int		fd;
	char	*line;
	size_t	total_written;
	char	*expanded;

	total_written = 0;
	fd = create_heredoc_tmpfile(path);
	if (fd < 0)
	{
		perror("tmpfile");
		return (1);
	}
	unlink(path);
	handle_signals_heredoc();
	while (1)
	{

		// line = readline("> "); // ONLY COMMENTED OUT TO TEST! COMMENT BACK IN

		//needs to be commented out
		if (isatty(fileno(stdin)))
			line = readline("> ");
		else
		{
			char *line_2;
			line_2 = read_file(fileno(stdin));
			line = ft_strtrim(line_2, "\n");
			free(line_2);
		}
		//
		if (g_signal_status == SIGINT)
		{
            if (line)
                free(line);
            close(fd);
            data->last_exit = 130;
            g_signal_status = 0;
            return (-1);
        }
		if (!line)
			break;
		if (ft_strcmp(line, hd->file) == 0)
		{
			free(line);
			break;
		}
		if (hd->expand)
		{
			expanded = expand_line(data, line);
			free(line);
			line = expanded;
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

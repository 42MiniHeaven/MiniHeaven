/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmpfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:01:44 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 19:45:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

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

static void	build_tmp_path(char *path, int counter, char *eof)
{
	size_t	i;
	long	num;

	num = (counter + (int)eof[0]) + (ft_strlen(eof) * counter);
	ft_strcpy(path, TMP_DIR "/.heredoc_");
	i = ft_strlen(path);
	append_number(path, &i, num);
	path[i++] = '_';
	append_number(path, &i, (long)counter);
	path[i] = '\0';
}

int	create_heredoc_tmpfile(char *path_out, char *eof)
{
	int	fd;
	int	attempt;

	attempt = 0;
	while (attempt < MAX_ATTEMPTS)
	{
		build_tmp_path(path_out, attempt, eof);
		fd = wopen(path_out, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		attempt++;
	}
	return (-1);
}

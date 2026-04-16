/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmpfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:01:44 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 17:24:53 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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

/*
 * DESCRIPTION
 * To create a temporary file for the heredoc a uniquie identifier is needed.
 * For this char *eof is casted into a hexadecimal address. To achieve this
 * an unsigned long is required resulting in a unique number.
 */

static void	build_tmp_path(char *path, int counter, char *eof)
{
	size_t			i;
	unsigned long	num;

	num = (unsigned long)eof;
	ft_strcpy(path, TMP_DIR "/.heredoc_");
	i = ft_strlen(path);
	append_number(path, &i, (long)num);
	path[i++] = '_';
	append_number(path, &i, (long)counter);
	path[i] = '\0';
}

/*
 * DESCRIPTION
 * In heredoc we are creating a temporary file to save the strings written 
 * in the terminal to later output them. 
 */

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

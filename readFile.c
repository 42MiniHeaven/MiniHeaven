/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readFile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:21:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 20:30:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static char	*joinfree(char *old, char *add)
{
	char	*new;

	new = ft_strjoin(old, add);
	free(old);
	return (new);
}

char	*read_file(int fd)
{
	ssize_t	bytes;
	char	buffer[BUFFER_SIZE + 1];
	char	*content;

	content = ft_strdup("");
//	fd = open(infile, O_RDONLY);
//	if (fd < 0)
//		return (free(content), NULL);
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		content = joinfree(content, buffer);
		if (!content)
			return (close(fd), NULL);
	}
	close(fd);
	if (bytes < 0)
		return (free(content), NULL);
	return (content);
}


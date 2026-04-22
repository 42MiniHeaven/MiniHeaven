/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readFile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:51:24 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/22 17:51:39 by lwittwer         ###   ########.fr       */
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

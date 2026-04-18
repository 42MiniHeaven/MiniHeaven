/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readFile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:21:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 19:42:07 by azielnic         ###   ########.fr       */
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

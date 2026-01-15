/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:15:33 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/15 21:10:58 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

#include <aio.h>
#include <stdlib.h>
//Idea: I want to create a Heredoc function that read input with read. into a buffer
//		Also i want to create a 2D String with the input from the user
//		I want to safe the delimiter in the struct and always check if the input is DELIM
//		I need to handle signels as readline would
//		I want to exit cleanly
//		and also expand correctly when we hav expansion on

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*cpys;
	size_t	i;

	i = 0;
	cpys = malloc(ft_strlen((s) + 1) * 1);
	if (!cpys)
		return (NULL);
	while (s[i])
	{
		cpys[i] = s[i];
		i++;
	}
	cpys[i] = '\0';
	return (cpys);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	lenstrjoin = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = malloc((lenstrjoin + 1) * sizeof(char));
	if (ptr == NULL)
		return (0);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void	mh_heredoc(char	**test)
{
	char	buff[2];
	ssize_t	bytes;
	int		i;
	char	*tmp;

	i = 0;
	bytes = 0;
	while (1)
	{
		if (i == 5)
			break;
		bytes = read(0, buff, 1);
		buff[bytes] = '\0';
		if (bytes == 0)
			i++;
		if (!test[i])
			test[i] = ft_strdup("");
//		if (bytes == -1)
//		{
//			if (errno == EINTR) // && g_interrupted)
//				printf("ABORT HEREDOC\n");
//			else
//				printf("real error\n");
//		}
		tmp = ft_strjoin(test[i], buff);
		if (!tmp)
		{
			//free(tesT);
			return;
		}
		free(test[i]);
		test[i] = tmp;
		printf("%s\n", test[i]);
	}
	test[i] = NULL;
}

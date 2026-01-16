/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:18:58 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/16 13:23:28 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (char)c;
		i++;
	}
	return ((void *)s);
}


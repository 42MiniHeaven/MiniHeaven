/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:13:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/24 23:40:06 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	lenstrjoin = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = ft_calloc(lenstrjoin + 2, sizeof(char));
	if (ptr == NULL)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = '=';
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	lenstrjoin = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = ft_calloc(lenstrjoin + 2, sizeof(char));
	if (ptr == NULL)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = ' ';
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}

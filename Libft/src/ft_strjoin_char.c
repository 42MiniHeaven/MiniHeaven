/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 20:22:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/24 20:25:05 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 || !s2 || !c)
		return (NULL);
	lenstrjoin = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ptr = ft_calloc(lenstrjoin + 1, sizeof(char));
	if (ptr == NULL)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}

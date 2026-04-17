/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:07:47 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/17 20:04:44 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *s, const char *check)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s || !check)
		return (NULL);
	while (s[i])
	{
		j = 0;
		while (check[j])
		{
			if (s[i] == (unsigned char)check[j])
				return ((char *)&s[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

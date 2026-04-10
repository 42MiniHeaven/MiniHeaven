/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:13:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/11 00:12:05 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lenstrjoin = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = ft_calloc(lenstrjoin +1, sizeof(char));
	if (ptr == NULL)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		ptr[i + j] = s2[j];
	return (ptr);
}
/*
//V2checked protected from both strings being 0
//V3 changed || from && check
#include <stdio.h>
int	main(void)
{
	char	*str = "l&l";
	char	*str1 = "L&L";
//	char	*str = NULL;
//	char	*str1 = NULL;
	char	*output;

	output = ft_strjoin(str, str1);
	printf("|%s|", output);
	free(output);
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:10:53 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/24 14:32:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("Mine: |%d|\n", ft_strcmp(argv[1], argv[2]));
		printf("Orig: |%d|\n", strcmp(argv[1], argv[2]));
	}
	else
		printf("Only 2 strings allowed\n");
	return (0);
}*/

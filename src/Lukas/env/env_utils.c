/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:45:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:22:26 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

//TODO: Lukas check comment otherwise remove
char	*get_key(const char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
//	if (str[i] != '=')
//		return (NULL);
	return (ft_substr(str, 0, i));
}

char	*get_value(const char *str)
{
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (NULL);
	i++;
	j = i;
	while (str[j])
		j++;
	return (ft_substr(str, i, j - i));
}

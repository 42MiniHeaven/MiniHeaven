/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:45:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 15:12:37 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

char	*get_key(const char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (NULL);
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

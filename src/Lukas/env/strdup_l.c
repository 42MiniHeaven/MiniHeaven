/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:15:26 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/20 19:34:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*strdup_l(char *s, size_t s, size_t l)
{
	size_t	i;
	char	*ret;

	if (!s1)
		return (NULL);
	ret = malloc((l + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (start + ++i < l)
		ret[i] = start[start + i];
	ret[i] = '\0';
	return (ret);
}

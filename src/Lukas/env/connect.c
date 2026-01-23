/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/23 15:07:13 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*File Description:	This file needs to be optimized for our merge*/

void	create_env(t_env **start, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;
	size_t	len;
	size_t	s;
	size_t	n;

	i = 0;
	while (envp[i])
	{
		s = 0;
		while (envp[i][s] && envp[i][s] != '=')
			s++;
		n = s + 1;
		len = ft_strlen(envp[i]);
		key = ft_substr(envp[i], 0, s);
		value = ft_substr(envp[i], n, len - n);
		env_add_back(start, env_new(key, value));
		i++;
	}
}

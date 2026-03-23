/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:33:26 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	env_init(t_environment *start, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;

	i = -1;
	while (envp[++i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (env_add(start, env_create_node(key, value)) == 0)
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:33:26 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/14 15:15:30 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

int	env_init(t_environment *start, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;
	int		flag;

	i = -1;
	while (envp[++i])
	{
		flag = 0;
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (value != NULL)
			flag = 1;
		if (env_add(start, env_create_node(key, value, flag)) == 0)
			return (0);
	}
	return (1);
}

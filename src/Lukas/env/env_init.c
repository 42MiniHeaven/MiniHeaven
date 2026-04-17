/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:33:26 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 17:52:44 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static char	*get_shlvl(char *shlvl)
{
	char	*ret;
	int		lvl;

	lvl = ft_atoi(shlvl) + 1;
	ret = ft_itoa(lvl);
	return (ret);
}

int	env_init(t_environment *start, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (ft_strcmp(key, "SHLVL") == 0)
		{
			tmp = get_shlvl(value);
			free(value);
			value = tmp;
			tmp = NULL;
		}
		if (env_add(start, env_create_node(key, value)) == 0)
			return (0);
	}
	return (1);
}

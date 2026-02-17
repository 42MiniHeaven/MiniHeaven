/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/17 17:16:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../include/miniheaven.h"

static char	*get_shlvl(char *str)
{
	char	*tmp;

	tmp = ft_itoa(ft_atoi(str) + 1);
	if (!tmp)
		return (free(str), NULL);
	free(str);
	return (tmp);
}
/**
 * @brief   Creates the environment list.
 *
 * This function creates the environment list of MiniHeaven.
 *
 * @param   start	Head of our linked list
 * @param   envp	Array of Strings containing our envp
 *					provided by the system.
 */

void	create_env_list(t_env **start, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;
	char	*tmp;
	size_t	s;

	i = -1;
	while (envp[++i])
	{
		s = 0;
		while (envp[i][s] && envp[i][s] != '=')
			s++;
		key = ft_substr(envp[i], 0, s);
		value = ft_substr(envp[i], s + 1, ft_strlen(envp[i]) - (s + 1));
		if (ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen("SHLVL")))
		{
			tmp = get_shlvl(value);
			value = tmp;
		}
		env_add_back(start, env_new(key, value));
		free(value);
		free(key);
	}
}

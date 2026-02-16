/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/16 16:13:19 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../include/miniheaven.h"

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
	size_t	s;
	size_t	n;

	i = 0;
	while (envp[i])
	{
		s = 0;
		while (envp[i][s] && envp[i][s] != '=')
			s++;
		n = s + 1;
		key = ft_substr(envp[i], 0, s);
		value = ft_substr(envp[i], n, ft_strlen(envp[i]) - n);
		if (ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0 && 
			(ft_strlen(key) == ft_strlen("SHLVL")))
			value = ft_itoa(ft_atoi(value) + 1);
		env_add_back(start, env_new(key, value));
		i++;
	}
}

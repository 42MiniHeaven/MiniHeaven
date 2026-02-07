/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:00 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 22:22:48 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../../include/execute.h"

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
		env_add_back(start, env_new(key, value));
		i++;
	}
}

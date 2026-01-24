/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:41:42 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/24 23:52:33 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../exec.h"

/**
 * @brief   Unsets environment variables specified in a command string.
 *
 * Splits the input command into tokens and calls env_unset() for each variable
 * name found.
 *
 * @param   data	Structure containing the environment linked list and envp.
 * @param   cmd		Command string containing variable names to remove.
 */

void	builtin_unset(t_exec data, char *cmd)
{
	char	**split;
	int		i;

	split = ft_split(cmd, ' ');
	if (!split)
		return ;
	i = 1;
	while (split[i])
	{
		env_unset(&data.env, split[i]);
		i++;
	}
	free_arr(split);
	split = NULL;
	data.envp = env_to_envp(data.env);
}

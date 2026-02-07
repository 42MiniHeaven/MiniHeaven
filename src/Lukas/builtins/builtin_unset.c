/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:41:42 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 23:00:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../../include/execute.h"

/**
 * @brief   Unsets environment variables specified in a command string.
 *
 * Splits the input command into tokens and calls env_unset() for each variable
 * name found.
 *
 * @param   data	Structure containing the environment linked list and envp.
 * @param   cmd		Command string containing variable names to remove.
 */

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	char	**split;
	int		i;

	split = ft_split(cmd->argv[0], ' ');
	if (!split)
		return (1);
	i = 1;
	while (split[i])
	{
		env_unset(env, split[i]);
		i++;
	}
	free_arr(split);
	split = NULL;
	return (0);
}

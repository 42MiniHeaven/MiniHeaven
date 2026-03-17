/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:55:38 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/17 17:02:52 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/miniheaven.h"

/**
 * @brief   Unsets environment variables specified in a command string.
 *
 * Splits the input command into tokens and calls env_unset() for each variable
 * name found.
 *
 * @param   data	Structure containing the environment linked list and envp.
 * @param   cmd		Command string containing variable names to remove.
 */
/*
int	builtin_unset(t_cmd *cmd, t_env *env)
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
*/
int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	if (!env || !cmd)
		return (0);
	i = 1;
	while (cmd[i])
	{
		env_unset(env, cmd[i]);
		i++;
	}
	return (0);
}

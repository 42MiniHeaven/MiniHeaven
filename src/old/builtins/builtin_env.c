/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:24:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/24 17:53:31 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/miniheaven.h"

/**
 * @brief   displays current environment
 *
 * env displays the current environment of the Shell
 *
 * @param   data	Struct containing env list and envp
 * @param   str		Input str
 */

int	builtin_env(t_cmd *cmd, t_env **env)
{
	t_env	*current;

	current = *env;
	if (cmd->argv[1])
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	while (current)
	{
		if (current->value[0] != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

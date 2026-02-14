/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:10:22 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:22:29 by lwittwer         ###   ########.fr       */
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
		ft_putstr_fd("Error", 2);
		return (1);
	}
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
//	mh.exit_status = 0;
	return (0);
}

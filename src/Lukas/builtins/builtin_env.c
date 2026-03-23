/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:34:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/**
 * @brief   displays current environment
 *
 * env displays the current environment of the Shell
 *
 * @param   data	Struct containing env list and envp
 * @param   str		Input str
 */

int	builtin_env(t_cmd *cmd, t_environment *list)
{
	if (cmd->argv[1])
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	while (list->head)
	{
		if (list->head->key[0] != '\0')
			printf("%s=%s\n", list->head->key, list->head->value);
		list->head = list->head->next;
	}
	return (0);
}

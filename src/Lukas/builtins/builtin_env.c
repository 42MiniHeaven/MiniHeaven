/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:34:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:20:01 by azielnic         ###   ########.fr       */
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

// TODO: update _ when using env (currently not correct)
int	builtin_env(t_cmd *cmd, t_environment *list)
{
	t_env	*tmp;

	if (cmd->argv[1])
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	tmp = list->head;
	while (tmp)
	{
		if (tmp->key[0] != '\0')
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:10:22 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/25 00:21:34 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../exec.h"

/**
 * @brief   displays current environment
 *
 * env displays the current environment of the Shell
 *
 * @param   data	Struct containing env list and envp
 * @param   str		Input str
 */

void	builtin_env(t_exec data, char *str)
{
	t_env	*current;

	current = data.env;
	if (ft_strchr(str, ' '))
	{
		ft_putstr_fd("Error", 2);
		return ;
	}
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	data.exit_status = 0;
}

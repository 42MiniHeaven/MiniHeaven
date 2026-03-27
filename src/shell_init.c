/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:04:42 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 15:48:51 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/**
 * @brief Initializes the shell environment list and stores the standard fds.
 *
 * Creates the internal environment list from the parent shell's `envp` array.
 * If `envp` is empty, a helper function is called to create a minimal default
 * environment list.
 *
 * Additionally, the current standard file descriptors (`stdin`, `stdout`,
 * `stderr`) are stored in the shell structure so they can be restored later
 * if they are modified during shell execution (e.g., through redirections).
 *
 * @param data  Pointer to the shell structure.
 * @param envp  NULL-term array of env variable strings from the parent shell.
 */

void	shell_init(t_shell *data, char **envp)
{
	t_environment	*list;

	list = malloc(sizeof(t_environment));
	if (!list)
		return ;
	list->head = NULL;
	if (envp[0] != NULL)
		env_init(list, envp);
	else
		env_init(list, empty_env());
	safe_std_fds(data);
	data->list = list;
}

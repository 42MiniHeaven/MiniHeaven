/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/15 16:49:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	child(t_cmd *cmds, t_environment *list)
{
	char	**envp;

	envp = env_arr(list->head);
	execve(resolve_path(cmds->argv[0], list->head), cmds->argv, envp);
	free_arr(envp);
	_exit(127);
}

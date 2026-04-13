/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 10:22:28 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	exec_single(t_shell *data)
{
	if (data->cmds->argv && data->cmds->argv[0]
		&& !is_builtin(data->cmds->argv[0]))
	{
		{
			if (data->cmds->redir)
				if (safe_std_fds(data))
					return (1);
		}
		data->last_exit = exec_builtin(data);
		if (data->cmds->redir && data->fds)
		{
			restore_std_fds(data->fds);
			close_backup_fds(data->fds); // added new
			data->fds = NULL; // added new
		}
	}
	else
		exec_external(data);
	return (0);
}

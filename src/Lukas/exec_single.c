/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 16:03:35 by lwittwer         ###   ########.fr       */
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
			if(safe_std_fds(data))
				return (1);
		}
		data->last_exit = exec_builtin(data);
		if (data->cmds->redir && data->fds)
			restore_std_fds(data->fds);
	}
	else
		exec_external(data);
	return (0);
}

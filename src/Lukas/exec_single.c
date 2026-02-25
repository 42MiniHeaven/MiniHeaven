/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:27:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 13:24:41 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_single(t_cmd *cmds, t_env *env, t_fds *fds)
{
	int	last_exit;

	last_exit = 0;
	if (is_builtin(cmds->argv[0]))
	{
		if (apply_redirections(cmds->redir) != 0)
		{
			restore_std_fds(fds);
			return (1);
		}
		last_exit = exec_builtin(cmds, env);
		restore_std_fds(fds);
		return (last_exit);
	}
	else
		return (last_exit = exec_external(cmds, env));
}

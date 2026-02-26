/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:27:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/26 16:43:05 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_single(t_cmd *cmds, t_env *env, t_fds *fds,
				int *last_exit, int *should_exit)
{
	int	exec_result;

	if (is_builtin(cmds->argv[0]))
	{
		if (apply_redirections(cmds->redir) != 0)
		{
			restore_std_fds(fds);
			*last_exit = 1;
			return (EXEC_OK);
		}
		exec_result = exec_builtin(cmds, env, last_exit, should_exit);
		restore_std_fds(fds);
		return (exec_result);
	}
	else
		return (exec_external(cmds, env, last_exit), EXEC_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:52:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/15 16:43:53 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_external(t_cmd *cmds, t_environment *list)
{
	pid_t	pid;
	int		status;

	(void)cmds;
	(void)list;

	pid = fork();
	if (pid < 0)
	{
		return (1);
	}
	if (pid == 0)
		child(cmds, list);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

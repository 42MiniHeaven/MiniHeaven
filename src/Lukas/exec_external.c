/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:40:24 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 12:53:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_external(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		//setup_child_signals();
		if (apply_redirections(cmds->redir))
			return (1);
		execve(resolve_path(cmds->argv[0], env), cmds->argv, lst_to_env(env));
		//perror("execve");
		//error message!
		exit (127);
	}
	waitpid(pid, &status, 0);
	return (status); // (extract_exit_status(status));
}

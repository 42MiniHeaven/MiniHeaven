/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:40:24 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/26 16:48:04 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_external(t_cmd *cmds, t_env *env, int *last_exit)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		*last_exit = 1;
		return (EXEC_OK);
	}
	if (pid == 0)
	{
		//setup_child_signals();
		if (apply_redirections(cmds->redir))
			exit(1);
		execve(resolve_path(cmds->argv[0], env), cmds->argv, lst_to_env(env));
		perror(cmds->argv[0]);
		exit (127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_exit = 128 + WTERMSIG(status);
		return (EXEC_OK);
}

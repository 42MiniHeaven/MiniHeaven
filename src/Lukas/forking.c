/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:05:14 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/09 22:36:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	dispatch_pipeline(t_cmd *cmds, t_env *env)
{
	int	fd[2];
	int	prev_fd = -1;
	pid_t	pid;
	int		status = 42;
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
			return (1);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (apply_redirections(cmd->redirs))
				exit(1);
			if (is_builtin(cmd->argv[0]))
				exit(exec_builtin(cmd, env));
			else
				execve(resolve_path(cmd->argv[0], env), cmd->argv, llist_to_env(env));
			perror(cmd->argv[0]);
			exit(127);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	return (status);	//extract_exit_status(status);
}

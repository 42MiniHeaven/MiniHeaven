/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:48:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 13:17:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static void	setup_child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fd)
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
	if (apply_redirections(cmd->redir))
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, env));
	else
		execve(resolve_path(cmd->argv[0], env), cmd->argv, lst_to_env(env));
	perror(cmd->argv[0]);
	exit(127);
}

static void	parent_cleanup(t_cmd *cmd, int prev_fd, int *fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		prev_fd = fd[0];
	}
	else
		prev_fd = -1;
}

int	exec_pipe(t_cmd *cmds, t_env *env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	prev_fd = -1;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
			return (1);
		pid = fork();
		if (pid == 0)
			setup_child_process(cmd, env, prev_fd, fd);
		parent_cleanup(cmd, prev_fd, fd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	return (status);
}

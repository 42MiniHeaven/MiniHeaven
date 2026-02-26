/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:48:50 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/26 17:02:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static void	setup_child_process(t_cmd *cmd, t_env *env, int prev_fd, int *fd)
{
	int	dummy_exit;
	int	dummy_should_exit;

	dummy_exit = 0;
	dummy_should_exit = 0;
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
		exit(exec_builtin(cmd, env, &dummy_exit, &dummy_should_exit), dummy_exit);
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

int	exec_pipe(t_cmd *cmds, t_env *env, int *last_exit)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;
	t_cmd	*cmd;

	prev_fd = -1;
	cmd = cmds;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
		{
			*last_exit = 1;
			return (EXEC_OK);
		}
		pid = fork();
		if (pid == 0)
			setup_child_process(cmd, env, prev_fd, fd);
		parent_cleanup(cmd, prev_fd, fd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*last_exit = WEXITSTATUS(status);
			else if
				*last_exit = 128 + WTERMSIG(status);
		}
	}
	return (EXEC_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:37:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/19 14:16:29 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static int	create_pipe(t_cmd *cmd, int *fd)
{
	if (cmd->next && pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static pid_t	fork_child(t_cmd *cmd, t_environment *l, int prev_fd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (cmd->next)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		child(cmd, l);
	}
	return (pid);
}

static void	parent_pipe_cleanup(t_cmd *cmd, int *prev_fd, int *fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

static void	wait_last_child(pid_t last_pid, int *last_exit)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*last_exit = 128 + WTERMSIG(status);
		}
	}
}

int	exec_pipe(t_shell *data)
{
	int		fd[2];
	int		prev_fd;
	pid_t	last_pid;
	pid_t	pid;

	prev_fd = -1;
	while (data->cmds)
	{
		if (create_pipe(data->cmds, fd))
		{
			data->last_exit = 1;
			return (0);
		}
		pid = fork_child(data->cmds, data->list, prev_fd, fd);
		if (pid < 0)
		{
			data->last_exit = 1;
			return (0);
		}
		last_pid = pid;
		parent_pipe_cleanup(data->cmds, &prev_fd, fd);
		data->cmds = data->cmds->next;
	}
	wait_last_child(last_pid, &data->last_exit);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:37:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 13:55:20 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	create_pipe(t_cmd *cmd, int *fd)
{
	if (cmd->next && pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static pid_t	fork_child(t_cmd *cmd, t_shell *data, int prev_fd, int *fd)
{
	pid_t	pid;

	pid = wfork();
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			wdup2(prev_fd, STDIN_FILENO);
			wclose(prev_fd);
		}
		if (cmd->next)
		{
			wclose(fd[0]);
			wdup2(fd[1], STDOUT_FILENO);
			wclose(fd[1]);
		}
//		close_all_fds();
		child(cmd, data);
	}
	return (pid);
}

static void	parent_pipe_cleanup(t_cmd *cmd, int *prev_fd, int *fd)
{
	if (*prev_fd != -1)
		wclose(*prev_fd);
	if (cmd->redir && cmd->redir->fd != -1)
		wclose(cmd->redir->fd);
	if (cmd->next)
	{
		wclose(fd[1]);
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
	t_cmd	*tmp;

	tmp = data->cmds;
	prev_fd = -1;
	while (tmp)
	{
		if (create_pipe(tmp, fd))
		{
			data->last_exit = 0;
			return (0);
		}
		pid = fork_child(tmp, data, prev_fd, fd);
		if (pid < 0)
		{
			data->last_exit = 0;
			return (0);
		}
		last_pid = pid;
		parent_pipe_cleanup(tmp, &prev_fd, fd);
		tmp = tmp->next;
	}
	wait_last_child(last_pid, &data->last_exit);
	return (0);
}

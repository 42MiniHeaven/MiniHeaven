/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:37:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/19 10:51:19 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_pipe(t_shell *data)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;

	prev_fd = -1;
	last_pid = -1;
	while (data->cmds)
	{
		if (data->cmds->next && pipe(fd) < 0)
		{
			perror("pipe");
			data->last_exit = 1;
			return (0);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			data->last_exit = 1;
			return (0);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (data->cmds->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			child(data->cmds, data->list);
		}
		last_pid = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (data->cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		else
			prev_fd = -1;
		data->cmds = data->cmds->next;
	}
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->last_exit = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

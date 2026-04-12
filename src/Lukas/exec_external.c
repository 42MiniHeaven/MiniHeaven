/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:52:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 20:56:54 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

void	wait_child(pid_t pid, t_shell *data)
{
	int	status;

	if (pid <= 0)
		return ;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		data->last_exit = 1;
		return ;
	}
	if (WIFEXITED(status))
		data->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signal_status = WTERMSIG(status);
		if (g_signal_status == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)", 18);
		write(STDOUT_FILENO, "\n", 1);
		data->last_exit = g_signal_status + 128;
		g_signal_status = 0;
	}
}

int	exec_external(t_shell *data)
{
	pid_t	pid;

	pid = wfork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		child(data->cmds, data);
	else
		wait_child(pid, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:52:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/04 17:52:03 by azielnic         ###   ########.fr       */
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
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		//data->last_exit = 128 + sig;
		g_signal_status = 0;
	}
	// else
	// 	data->last_exit = 1;
}

int	exec_external(t_shell *data)
{
	pid_t	pid;

	handle_signals_exec_parent(); // have to remove this after wfork is implemented
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		child(data->cmds, data->list);
	else
		wait_child(pid, data);
	return (0);
}

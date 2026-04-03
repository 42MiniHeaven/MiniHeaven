/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:52:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/03 23:11:29 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	wait_child(pid_t pid, t_shell *data)
{
	int	status;
	int	sig;

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
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		data->last_exit = 128 + sig;
	}
	else
		data->last_exit = 1;
}

int	exec_external(t_shell *data)
{
	pid_t	pid;

	//TODO: ignore signals for  parent before fork
	// signal_parent();
	pid = fork();
	if (pid < 0)
	{
		return (1);
	}
	if (pid == 0)
		child(data->cmds, data->list);
	else
		wait_child(pid, data);
	return (0);
}

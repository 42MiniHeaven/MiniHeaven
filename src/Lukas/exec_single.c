/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/19 17:25:52 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

int	exec_builtin(t_cmd *cmds, t_shell *data)
{
	if (setup_redirections(data->cmds->redir) == -1)
		return (1);
	if (!data || !cmds || !cmds->argv || !cmds->argv[0])
		return (0);
	if (ft_strcmp(cmds->argv[0], "cd") == 0)
		return (builtin_cd(cmds, data->list));
	if (ft_strcmp(cmds->argv[0], "echo") == 0)
		return (builtin_echo(cmds, data->list));
	if (ft_strcmp(cmds->argv[0], "env") == 0)
		return (builtin_env(cmds, data->list));
	if (ft_strcmp(cmds->argv[0], "exit") == 0)
		return (builtin_exit(cmds, data));
	if (ft_strcmp(cmds->argv[0], "export") == 0)
		return (builtin_export(cmds, data->list));
	if (ft_strcmp(cmds->argv[0], "pwd") == 0)
		return (builtin_pwd(data->cmds, data->list));
	if (ft_strcmp(cmds->argv[0], "unset") == 0)
		return (builtin_unset(cmds, data->list));
	return (0);
}

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

int	exec_single(t_shell *data)
{
	if (data->cmds->argv && data->cmds->argv[0]
		&& !is_builtin(data->cmds->argv[0]))
	{
		if (data->cmds->redir)
			if (safe_std_fds(data))
				return (1);
		data->last_exit = exec_builtin(data->cmds, data);
		if (data->cmds->redir && data->fds)
		{
			restore_std_fds(data->fds);
			close_backup_fds(data->fds);
			data->fds = NULL;
		}
	}
	else
		exec_external(data);
	return (0);
}

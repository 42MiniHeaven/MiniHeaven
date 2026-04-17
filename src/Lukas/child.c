/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 20:05:55 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

//TODO: Info: added close_redir_fds() which fixed the leak

void	child(t_cmd *cmds, t_shell *data)
{
	close_all_fds();
	data->envp = NULL;
	data->path = NULL;
	handle_signals_exec_child();
	if (!cmds)
		exit (0);
	if (setup_redirections(cmds->redir) == -1)
		return (close_redir_fds(), exit_child(data, errno, NULL, NULL));
	if (!cmds->argv || cmds->argv[0] == NULL)
		return (close_redir_fds(), exit_child(data, errno, NULL, NULL));
	data->envp = env_arr(data->list->head);
	data->path = resolve_path(cmds->argv[0], data->list->head);
	if (!data->path)
	{
		close_redir_fds();
		exit_child(data, errno, cmds->argv[0], ": command not found\n");
	}
	execve(data->path, cmds->argv, data->envp);
	close_redir_fds();
	if (errno == EACCES)
		exit_child(data, errno, cmds->argv[0], ": permission denied\n");
	if (data->cmds->redir && data->cmds->redir->file)
		exit_child(data, errno, cmds->argv[0], "No such file or directory\n");
	exit_child(data, errno, cmds->argv[0], ": Is a directory\n");
}

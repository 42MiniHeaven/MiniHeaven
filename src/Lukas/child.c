/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 17:48:16 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_shell *data)
{
	data->envp = NULL;
	data->path = NULL;
	handle_signals_exec_child();
	if (!cmds)
		exit (0);
	setup_redirections(data->cmds->redir);
	data->envp = env_arr(data->list->head);
	data->path = resolve_path(cmds->argv[0], data->list->head);
	if (!data->path)
		exit_child(data, errno, cmds->argv[0], ": command not found\n");
//		child_error(cmds->argv[0], ": command not found\n"); //TODO: FIX!
	execve(data->path, cmds->argv, data->envp);
	if (errno == EACCES)
		exit_child(data, errno, cmds->argv[0], ": permission denied\n");
	else
	{
		if (data->cmds->redir && data->cmds->redir->file)
			exit_child(data, errno, cmds->argv[0], "No such file or directory\n");
		exit_child(data, errno, cmds->argv[0], "no clue what belongs here\n");
	}
}

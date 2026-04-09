/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 21:30:13 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_shell *data)
{
	char	**envp;
	char	*path;
	int		exit_code;

	handle_signals_exec_child();
	if (!cmds)
		exit (0);
	setup_redirections(data->cmds->redir);
	envp = env_arr(data->list->head);
	path = resolve_path(cmds->argv[0], data->list->head);
	if (!path)
	{
		child_error(cmds->argv[0], ": command not found\n");
		exit_child(data, envp, path, 127);
	}
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
	{
		child_error(cmds->argv[0], ": permission denied\n");
		exit_code = 126;
	}
	else
	{
		if (data->cmds->redir && data->cmds->redir->file)
			child_error(cmds->redir->file, ": No such file or directory\n");
		exit_code = 127;
	}
	exit_child(data, envp, path, exit_code);
//	free(path);
//	free_arr(envp);
//	exit(exit_code);
}

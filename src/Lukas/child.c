/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 14:27:52 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_shell *data)
{
	char	**envp;
	char	*path;
	int		exit_code;

	handle_signals_exec_child();
	setup_redirections(cmds->redir);
	envp = env_arr(data->list->head);
	path = resolve_path(cmds->argv[0], data->list->head);
	close_all_fds();
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
	{
		exit_code = 126;
		exit_child(data, envp, path, exit_code, ":permission denied\n");
	}
	else
	{
		exit_code = 127;
		if (cmds->redir && cmds->redir->file)
			exit_child(data, envp, path, exit_code, ":No such file or directory\n");
	}
}

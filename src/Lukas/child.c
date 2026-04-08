/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 12:53:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_environment *list)
{
	char	**envp;
	char	*path;
	int		exit_code;

	handle_signals_exec_child();
	if (!cmds)
		exit (0);
	setup_redirections(cmds->redir);
	envp = env_arr(list->head);
	path = resolve_path(cmds->argv[0], list->head);
	if (!path)
	{
		child_error(cmds->argv[0], ": command not found\n");
		free_arr(envp);
		exit(127);
	}
	close_all_fds();
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
	{
		child_error(cmds->argv[0], ": permission denied\n");
		exit_code = 126;
	}
	else
	{
		if (cmds->redir && cmds->redir->file)
			child_error(cmds->redir->file, ": No such file or directory\n");
		exit_code = 127;
	}
	free(path);
	free_arr(envp);
	exit(exit_code);
}

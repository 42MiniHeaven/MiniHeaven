/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/05 20:10:04 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_environment *list)
{
	char	**envp;
	char	*path;

	handle_signals_exec_child();
	if (!cmds || !cmds->argv || !cmds->argv[0])
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
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
		child_error(cmds->argv[0], ": permission denied\n");
	else
		child_error(cmds->argv[0], ": No such file or directory");
	free(path);
	free_arr(envp);
	exit((errno == EACCES) ? 126 : 127);
}

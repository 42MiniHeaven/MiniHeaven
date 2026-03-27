/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 20:00:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	child(t_cmd *cmds, t_environment *list)
{
	char	**envp;
	char	*path;

	if (!cmds || !cmds->argv || !cmds->argv[0])
		exit (0);
	if (setup_redirections(cmds->redir))
		exit(1);
	envp = env_arr(list->head);
	path = resolve_path(cmds->argv[0], list->head);
	if (!path)
	{
		child_error(cmds->argv[0], ": command not found\n");
//		printf("%s: command not found\n", cmds->argv[0]);
		free_arr(envp);
		exit(127);
	}
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
		child_error(cmds->argv[0], ": permission denied\n");
		//printf("%s: permission denied\n", cmds->argv[0]);
	else
		perror(cmds->argv[0]);
	free(path);
	free_arr(envp);
	exit((errno == EACCES) ? 126 : 127);
}

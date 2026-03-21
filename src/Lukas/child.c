/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/21 22:43:46 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	child(t_cmd *cmds, t_environment *list)
{
	char	**envp;
	char	*path;

	printf("2\n");
	if (!cmds || !cmds->argv || !cmds->argv[0])
		exit (0);
	if (setup_redirections(cmds->redir))
		exit(1);
	envp = env_arr(list->head);
	path = resolve_path(cmds->argv[0], list->head);
	if (!path)
	{
		printf("%s: command not found\n", cmds->argv[0]);
		free_arr(envp);
		exit(127);
	}
	execve(path, cmds->argv, envp);
	if (errno == EACCES)
		printf("%s: permission denied\n", cmds->argv[0]);
	else
		perror(cmds->argv[0]);
	free(path);
	free_arr(envp);
	exit((errno == EACCES) ? 126 : 127);
}

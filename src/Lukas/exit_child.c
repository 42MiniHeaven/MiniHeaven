/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:31:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 20:01:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	exit_child(t_shell *data, char **envp, char *path, int exit_code)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->list)
		free_environment(data->list);
	if (envp)
		free_arr(envp);
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (data->input)
		free(data->input);
	close_backup_fds(data->fds);
	exit(exit_code);
}

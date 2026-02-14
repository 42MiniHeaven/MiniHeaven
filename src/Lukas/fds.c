/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:47:24 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 17:46:30 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	safe_std_fds(t_shell *data)
{
	t_fds	*saved;

	saved = malloc(sizeof(t_fds));
	if (!saved)
		return (1);
	saved->in = dup(STDIN_FILENO);
	saved->out = dup(STDOUT_FILENO);
	saved->err = dup(STDERR_FILENO);
	if (saved->in < 0 || saved->out < 0 || saved->err < 0)
	{
		free(saved);
		return (1);
	}
	data->fds = saved;
	return (0);
}

void	restore_std_fds(t_fds *saved)
{
	if (saved->in != -1)
	{
		dup2(saved->in, STDIN_FILENO);
		close(saved->in);
	}
	if (saved->out != -1)
	{
		dup2(saved->out , STDOUT_FILENO);
		close(saved->out);
	}
	if (saved->err != -1)
	{
		dup2(saved->err, STDERR_FILENO);
		close(saved->err);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:54:53 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 15:51:01 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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
		dup2(saved->in, STDOUT_FILENO);
		close(saved->out);
	}
	if (saved->err != -1)
	{
		dup2(saved->err, STDERR_FILENO);
		close(saved->err);
	}
}


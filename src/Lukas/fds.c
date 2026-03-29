/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:54:53 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/29 15:42:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	safe_std_fds(t_shell *data)
{
	t_fds	*saved;

	saved = ft_calloc(1, sizeof(t_fds));
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
	dup2(saved->in, STDIN_FILENO);
	dup2(saved->in, STDOUT_FILENO);
	dup2(saved->err, STDERR_FILENO);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:54:53 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/07 18:02:46 by lwittwer         ###   ########.fr       */
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
	wdup2(saved->in, STDIN_FILENO);
	wdup2(saved->out, STDOUT_FILENO);
	wdup2(saved->err, STDERR_FILENO);
}

void	close_all_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		wclose(fd);
		fd++;
	}
}

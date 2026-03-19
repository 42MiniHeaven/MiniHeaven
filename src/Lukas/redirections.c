/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/19 10:51:38 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	setup_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type ==  REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(redir->file), 1);
		dup2(fd, redir->fd);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

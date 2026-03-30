/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 18:49:11 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	setup_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = wopen(redir->file, O_RDONLY, 0);
		else if (redir->type == REDIR_OUT)
		{
			printf("entered redirout\n");
			fd = wopen(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
			fd = wopen(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		wdup2(fd, redir->fd);
		wclose(fd);
		redir = redir->next;
	}
	printf("exit\n");
}

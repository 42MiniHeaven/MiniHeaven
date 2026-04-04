/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/04 14:06:25 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	setup_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = wopen(redir->file, O_RDONLY, 0);
			wdup2(fd, STDIN_FILENO);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = wopen(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			wdup2(fd, STDOUT_FILENO);
		}
		else if (redir->type == HEREDOC)
		{
			wdup2(redir->fd, STDIN_FILENO);
			close(redir->fd);
			redir = redir->next;
			continue;
		}
		else if (redir->type == APPEND)
		{
			fd = wopen(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			wdup2(fd, STDOUT_FILENO);
		}
		wclose(fd);
		redir = redir->next;
	}
}

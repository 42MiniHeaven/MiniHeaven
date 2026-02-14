/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:39:49 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 18:18:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
				return (perror(redir->file), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == HEREDOC)
		{
			dup2(redir->fd, STDIN_FILENO);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

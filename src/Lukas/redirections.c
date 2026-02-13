/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:39:49 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/13 15:56:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	apply_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
				return (perror(redir->target), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			printf("test\n");
			fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->target), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->target), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			dup2(redir->fd, STDIN_FILENO);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

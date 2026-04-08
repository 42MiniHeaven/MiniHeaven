/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/06 21:15:39 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	setup_redir_in(t_redir *redir)
{
	int	fd;

	fd = wopen(redir->file, O_RDONLY, 0);
	wdup2(fd, STDIN_FILENO);
	return (fd);
}

static int	setup_redir_out(t_redir *redir)
{
	int	fd;

	fd = wopen(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	wdup2(fd, STDOUT_FILENO);
	return (fd);
}

static int	setup_redir_heredoc(t_redir *redir)
{
	wdup2(redir->fd, STDIN_FILENO);
	return (redir->fd);
}

static int	setup_redir_append(t_redir *redir)
{
	int	fd;

	fd = wopen(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	wdup2(fd, STDOUT_FILENO);
	return (fd);
}
void	setup_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = setup_redir_in(redir);
		else if (redir->type == REDIR_OUT)
			fd = setup_redir_out(redir);
		else if (redir->type == HEREDOC)
			fd = setup_redir_heredoc(redir);
		else if (redir->type == APPEND)
			fd = setup_redir_append(redir);
		wclose(fd);
		redir = redir->next;
	}
}

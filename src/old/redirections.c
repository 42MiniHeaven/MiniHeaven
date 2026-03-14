/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:20:12 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 13:42:10 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static int	apply_in(t_redir *redir, int fd)
{
	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_out(t_redir *redir, int fd)
{
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_append(t_redir *redir, int fd)
{
	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_heredoc(t_redir *redir)
{
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (0);
}

int	apply_redirections(t_redir *redir)
{
	int	fd;
	int	ret;

	fd = -1;
	ret = 0;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			ret = apply_in(redir, fd);
		else if (redir->type == REDIR_OUT)
			ret = apply_out(redir, fd);
		else if (redir->type == APPEND)
			ret = apply_append(redir, fd);
		else if (redir->type == HEREDOC)
			ret = apply_heredoc(redir);
		if (ret > 0)
			return (ret);
		redir = redir->next;
	}
	return (0);
}

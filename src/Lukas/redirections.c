/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 16:38:43 by lwittwer         ###   ########.fr       */
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
	int	fd;

	fd = wopen(redir->tmp_file, O_RDONLY, 0);
	wdup2(fd, STDIN_FILENO);
	return (fd);
}

static int	setup_redir_append(t_redir *redir)
{
	int	fd;

	fd = wopen(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	wdup2(fd, STDOUT_FILENO);
	return (fd);
}

int	setup_redirections(t_redir *redir)
{
	int		fd;
	t_redir	*tmp;

	if (!redir)
		return (0);
	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			fd = setup_redir_in(tmp);
		else if (tmp->type == REDIR_OUT)
			fd = setup_redir_out(tmp);
		else if (tmp->type == HEREDOC)
			fd = setup_redir_heredoc(tmp);
		else if (tmp->type == APPEND)
			fd = setup_redir_append(tmp);
		tmp = tmp->next;
	}
	if (fd == -1)
		return (-1);
	wclose(fd);
	return (0);
}

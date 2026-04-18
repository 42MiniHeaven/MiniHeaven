/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:56:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 20:04:56 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	setup_redir_in(t_redir *redir)
{
	int	check;

	if (!redir->success)
		return (-1);
	redir->fd = wopen(redir->file, O_RDONLY, 0);
	if (redir->fd == -1)
		return (-1);
	check = wdup2(redir->fd, STDIN_FILENO);
	if (check == -1)
		return (-1);
	return (0);
}

static int	setup_redir_out(t_redir *redir)
{
	int	check;

	if (!redir->success)
		return (-1);
	redir->fd = wopen(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		return (-1);
	check = wdup2(redir->fd, STDOUT_FILENO);
	if (check == -1)
		return (-1);
	return (0);
}

static int	setup_redir_heredoc(t_redir *redir)
{
	int	check;

	redir->fd = wopen(redir->tmp_file, O_RDONLY, 0);
	if (redir->fd == -1)
		return (-1);
	check = wdup2(redir->fd, STDIN_FILENO);
	if (check == -1)
		return (-1);
	return (0);
}

static int	setup_redir_append(t_redir *redir)
{
	int	check;

	if (!redir->success)
		return (-1);
	redir->fd = wopen(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
		return (-1);
	check = wdup2(redir->fd, STDOUT_FILENO);
	if (check == -1)
		return (-1);
	return (0);
}

int	setup_redirections(t_redir *redir)
{
	t_redir	*tmp;
	int		check;

	if (!redir)
		return (0);
	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			check = setup_redir_in(tmp);
		else if (tmp->type == REDIR_OUT)
			check = setup_redir_out(tmp);
		else if (tmp->type == HEREDOC)
			check = setup_redir_heredoc(tmp);
		else if (tmp->type == APPEND)
			check = setup_redir_append(tmp);
		if (check == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

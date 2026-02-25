/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:08:18 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:52:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, redir->file) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	redir->fd = fd[0];
	return (0);
}

int	handle_all_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redir;
		while (r)
		{
			if (r->type == HEREDOC)
			{
				if (handle_heredoc(r))
					return (1);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

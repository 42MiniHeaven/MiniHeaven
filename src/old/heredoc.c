/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:41:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 17:31:21 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	line = NULL;
	if (pipe(fd) < 0)
		return (1);
	while (1)
	{
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:22:37 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 20:41:33 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit (130);
}

static void	heredoc_child(t_redir *redir, int write_fd)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		line = readline("> ");
		if (!line)
			exit (0);
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
}

int	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(redir, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		return (1);
	}
	redir->fd = fd[0]; 
	return (0);
}

int	handle_all_heredocs(t_cmd *cmds) // TODO: heredoc needs to be moved to parser
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:13:01 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/18 15:19:13 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	wclose(int fd)
{
	if (fd < 0)
		return (-1);
	return (close(fd));
}

int	wdup2(int oldfd, int newfd)
{
	int	check;

	if (oldfd < 0 || newfd < 0)
		return (-1);
	check = dup2(oldfd, newfd);
	if (check == -1)
		return (-1);
	return (0);
}

int	wpipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_error("wpipe", "could not pipe", 2);
		return (1);
	}
	return (0);
}

pid_t	wfork(void)
{
	pid_t	pid;

	handle_signals_exec_parent();
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

int	wopen(const char *path, int flags, mode_t mode)
{
	int		fd;
	char	*err;

	fd = open(path, flags, mode);
	if (fd < 0)
	{
		err = ft_strjoin(": ", strerror(errno));
		if (!err)
			return (-1);
		ft_error((char *)path, err, 2);
		free(err);
		return (-1);
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:22:03 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 17:06:01 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "externals.h"

extern char	**environ;

static void	child(char **bla)
{
	(void)bla;
	char	*argv[] = {"/usr/bin/ls", 0};
	execve("/usr/bin/ls", argv, environ);
}

void	run_external(char **argv)
{
	int	status;
	pid_t	c;
	c = fork();
	if (c == 0)
		child(argv);
	waitpid(c, &status, 0);
	return;
}

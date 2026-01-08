/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:27:03 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/08 16:30:31 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static void	child(int nb)
{
	printf("Hello i am child number: %i\n", nb);
	fflush(stdout);
	exit(0);
}

static pid_t	create_fork(int nb)
{
	pid_t	c;

	c = fork();
	if (c == 0)
		child(nb);
	return (c);
}

int	forking(int children)
{
	int		status[children];
	pid_t	process[children];
	int	i = 0;
	while(i < children)
	{
		process[i] = create_fork(i);
		i++;
	}
	i = 0;
	while(i < children)
	{
		waitpid(process[i], &status[i], 0);
		i++;
	}
	return (0);
}

int	main()
{
	forking(3);
	return(0);
}

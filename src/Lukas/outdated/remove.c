/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:27:03 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/09 19:32:36 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"
#include <string.h>

static void	child(int nb, int read_fd, int write_fd, int is_last)
{
	char	buffer[1024] = {0};

	if(read_fd != -1)
	{
		read(read_fd, buffer, sizeof(buffer));
		close(read_fd);
	}
	char mynum[32];
	snprintf(mynum, sizeof(mynum), "%d", nb);
	strncat(buffer, mynum, sizeof(buffer) - strlen(buffer) - 1);
	if(is_last)
	{
		printf("Final output: %s\n", buffer);
		fflush(stdout);
	}
	else
	{
		write(write_fd, buffer, strlen(buffer) + 1);
	}
	close(write_fd);
	exit(0);
}

static pid_t	create_fork(int nb, int read_fd, int write_fd, int is_last)
{
	pid_t	c;

	c = fork();
	if (c == 0)
		child(nb, read_fd, write_fd, is_last);
	return (c);
}

int	forking(t_exec *test)
{
	int	prev_read = -1;
	int	i = 0;
	while(i < test->args)
	{
		if(i < test->args - 1)
		{
			if(pipe(test->pipefd) == -1)
				exit(2);
		}
		else
		{
			test->pipefd[0] = -1;
			test->pipefd[1] = -1;
		}
		test->process[i] = create_fork(i, prev_read, test->pipefd[1], i == test->args - 2);
		if (prev_read != -1)
			close(prev_read);
		if (test->pipefd[1] != -1)
			close(test->pipefd[1]);
		prev_read = test->pipefd[0];
		i++;
	}
	i = 0;
	while(i < test->args)
	{
		waitpid(test->process[i], &test->status[i], 0);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_exec	test;
	int	size;

	if(argc == 1)
		exit(1);	
	size = atoi(argv[1]);
	if(argc > 0)
	{
		test.args = size;
		test.status = malloc(size * sizeof(int));
		test.process = malloc(size * sizeof(pid_t));
		forking(&test);
	}
	//free
	return(0);
}

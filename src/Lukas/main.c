/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 21:19:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	t_cmd	cmd;
	char	**path = envp;

	if (argc == 1)
		return (1);
	i = atoi(argv[1]);
	if (i == 0)		//create real case
	{
		char *argv[] = {"ls", "-l", NULL};
	
		cmd.argv = argv;
		cmd.flag = 0;
		cmd.envp = path;
		cmd.in_fd = STDIN_FILENO;
		cmd.out_fd = STDOUT_FILENO;
		cmd.next = NULL;
	}
	if (i == 1)
	{
		char *argv[] = {"ls", "-l", NULL};
	
		cmd.argv = argv;
		cmd.flag = 1;
		cmd.envp = path;
		cmd.in_fd = STDIN_FILENO;
		cmd.out_fd = STDOUT_FILENO;
		cmd.next = NULL;
	}
	if (i == 2)		//create real case
	{
		char *argv[] = {"ls", "-l", NULL};
	
		cmd.argv = argv;
		cmd.flag = 2;
		cmd.envp = path;
		cmd.in_fd = STDIN_FILENO;
		cmd.out_fd = STDOUT_FILENO;
		cmd.next = NULL;
	}
	if (i == 3)		//create real case
	{
		char *argv[] = {"ls", "-l", NULL};
	
		cmd.argv = argv;
		cmd.flag = 3;
		cmd.envp = path;
		cmd.in_fd = STDIN_FILENO;
		cmd.out_fd = STDOUT_FILENO;
		cmd.next = NULL;
	}
	if (i == 4)		//create real case
	{
		char *argv[] = {"ls", "-l", NULL};
	
		cmd.argv = argv;
		cmd.flag = 4;
		cmd.envp = path;
		cmd.in_fd = STDIN_FILENO;
		cmd.out_fd = STDOUT_FILENO;
		cmd.next = NULL;
	}
	decider(cmd);
	return (0);
}

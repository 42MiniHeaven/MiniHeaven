/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/09 16:22:53 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	main(int argc, char **argv, char **envp)
{
	t_mh	data;
	t_cmd	cmd;
	t_cmd	cmd2;
	t_cmd	cmd3;
	(void)argc;
	(void)argv;
	char *test[] = {"ls", "env", NULL};
	char *test2[] = {"grep", "t", NULL};
	char *test3[] = {"wc", "-l", NULL};

	cmd.argv = test;
	cmd.next = &cmd2;
	cmd2.argv = test2;
	cmd2.next = &cmd3;
	cmd3.argv = test3;
	cmd3.next = NULL;
	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
	data.cmds = cmd;
	/*
	char	*in; //input string
	while(1)
	{
		in = readline("MiniHeaven> ");
		if (!in)
		{
			free(in); //dont know if we need this
			exit(0);
		}
		if (in)
		{
			printf("%s\n", in); //pass to parser
			add_history(in);
		}
		free(in);
	}*/
	//parser&&lexer
	dispatcher(&data.cmds, data.llist);
	return (0);
}

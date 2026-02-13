/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/13 21:03:56 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	main(int argc, char **argv, char **envp)
{
	t_mh	data;
	t_cmd	cmd;
	t_redir	redir;
	t_std_fds	fds;
	t_cmd	cmd2;
	t_cmd	cmd3;
	(void)argc;
	(void)argv;
	char *test[] = {"export", "test=123", NULL};
//	char target[] = "test";
	char *test2[] = {"export", NULL};
	char *test3[] = {"env", NULL};

	if (safe_std_fds(&fds) != 0)
		return (42);
	cmd.argv = test;
	cmd.next = &cmd2;
//	redir.target = target;
//	redir.type = REDIR_HEREDOC;
	redir.next = NULL;
	cmd.redirs = &redir;
	cmd.stdfds = &fds;
	cmd2.argv = test2;
	cmd2.next = &cmd3;
	cmd2.redirs = NULL;
	cmd3.argv = test3;
	cmd3.redirs = NULL;
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

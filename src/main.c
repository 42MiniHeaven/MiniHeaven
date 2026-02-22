/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/22 22:22:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

// PROBLEM: Currently when enter is pressed it adds it to the history.

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals);
		input = readline("MiniHeaven> ");
		if (!input)	// should only be triggered by ctrl+d not by ctrl+c
			break;
		if (input)
		{
			add_history(input);
			lexer(&data, input);
		}
		data.cmds = parse(data.tokens);
		dispatcher(data.cmds, data.llist, data.fds);
		free(input);
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char				*input;
// 	t_shell				data;
// 	// struct sigaction	sa;
	
// 	// sa.sa_handler = &handle_signals;
// 	ft_memset(&data, 0, sizeof(data));
// 	init_shell(&data, envp);
// 	int i = 0;
// 	while (i++ < argc -1)
// 	{
// 		input = argv[i];
// 		if (!input)
// 			break;	//exit(0);
// 		if (input)
// 		{
// 			add_history(input);
// 			lexer(&data, input);
// 		}
// 		data.cmds = parse(data.tokens);
// 		dispatcher(data.cmds, data.llist, data.fds);
// 	}
// 	return (0);
// }

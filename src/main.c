/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/22 23:17:46 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

#include <sys/ioctl.h>

/*
 * DESCRIPTION
 *		The ioctl function  the second variable TIOCSTI fakes input a
 */
int	hook_main(void)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
	rl_signal_event_hook = hook_main;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signals);
		input = readline("MiniHeaven> ");
		if (!input)	// should only be triggered by ctrl+d not by ctrl+c
			break;
		if (input)
		{
			if (ft_strlen(input) > 0)
				add_history(input);
			lexer(&data, input);
		}
		data.cmds = parse(data.tokens);
		dispatcher(data.cmds, data.llist, data.fds);
		free_call(data, 0, input);
	}
	free_call(data, 1, input);
	return (0);
}


// ------------------ ONLY FOR VS CODE DEBUGGING -------------------------

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/11 21:31:22 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

/* 
 * GENERAL:
 * 		The main currently displays a prompt and reads input. 
 * 
 * IMPLEMENTED:		
 * 		-readline 
 * 		-history
 * 		-ctrl-\ (should do nothing according to the subject)
 * 
 * TO BE IMPLEMENTED:
 * 		-exit builtin
 * 		-ctrl+d handling (needs its own signal handler)
 * 		-ctrl+c handling (needs its own signal handler)
 */

int	main(int argc, char **argv, char **envp)
{
	char	*input; //input string

	(void) argc;
	(void) argv;
	(void) envp;
	signal(SIGQUIT, SIG_IGN); // ctrl-\ signal is ignored
	while(1)
	{
		input = readline("MiniHeaven> ");
		if (!input)
		{
			break;
			//exit(0);
		}
		if (input)
		{
			printf("%s", input); //pass to parser
			if (input[0] != '\0')
			{
				printf("\n");
				add_history(input);
			}
		}
		free(input);
	}
	return (0);
}

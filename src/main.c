/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 20:38:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	data;

	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("MiniHeaven> ");
		if (!input)
			break;	//exit(0);
		if (input)
		{
			add_history(input);
			data.tokens = lexer(input);
		}
		data.cmds = parse(data.tokens);
		dispatcher(data.cmds, data.llist, data.fds);
		free(input);
	}
	return (0);
}

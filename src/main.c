/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:54:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 19:52:50 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	data;
	int		ecode;//different name maybe

	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
	(void)argc;
	(void)argv;
	while (1) //and status not true!!
	{
		input = readline("MiniHeaven> ");
		if (!input)
			break ;
		if (input)
		{
			if (ft_strlen(input) > 0)
				add_history(input);
			lexer(&data, input);
		}
		data.cmds = parse(data.tokens);
		dispatcher(data.cmds, data.lst, data.fds, &data.status);
		free_call(data, 0, input);
	}
	ecode = data.status;
	free_call(data, 1, input);
	return (ecode);
}

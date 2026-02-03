/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/03 22:01:55 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	main(int argc, char **argv, char **envp)
{
	t_mh	data;
	(void)argc;
	(void)argv;
	char *test[] = {NULL};

	ft_memset(&data, 0, sizeof(data));
	init_shell(&data, envp);
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
	execute(test, data.env);
	return (0);
}

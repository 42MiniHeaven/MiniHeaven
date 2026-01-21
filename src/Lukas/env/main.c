/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/21 17:50:21 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec	data = {NULL, NULL, 0};
	(void)argc;
	(void)argv;
	char	*in; //input string

	create_env(&data.env, envp);
	data.envp = env_to_envp(data.env);
	if (!data.envp)
		return (free_linked(data.env), 1);
	int	i = -1;
	while (data.envp[++i])
		printf("%s\n", data.envp[i]);
	while(1 && i < 55)
	{
		in = readline("MiniHeaven> ");
		if (!in)
		{
			free(in); //dont know if we need this
			exit(0);
		}
		if (in)
		{
			//printf("%s\n", in); //pass to parser
			add_history(in);
		}
		free(in);
		i++;
	}
	free_arr(data.envp);
	free_linked(data.env);
	return (0);
}

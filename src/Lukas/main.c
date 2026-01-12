/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/12 21:34:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/exec.h"
#include "executor.h"

int	main(int argc, char **argv, char **envp)
{
	char	*argv_ls[] = {"ls", "-l", 0};
	char	*env;

	t_command cmd = {
		.argv = argv_ls,
		.input_file = 0,
		.output_file = 0,
		.append = 0
	};

	t_pipeline p = {
		.cmds = &cmd,
		.count = 1
	};
	(void)argc;
	(void)argv;
//	(void)envp; auskommentiert fuers testen
	env = strdup(ret_env(envp));
	printf("%s\n", env);
	decider(p, envp);
	free(env);
	return (0);
}

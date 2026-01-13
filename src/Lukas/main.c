/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:19 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/13 15:49:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/exec.h"
#include "executor.h"

int	main(int argc, char **argv, char **envp)
{
	//int		i = 0;
	char	**arr;
//	char	*absolute;
//	char	*relative;
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
	env = strdup(ret_unresolved(envp)); //use ft_strdup
//	printf("%s\n", env);
	arr = ret_patharr(env);
//	while(arr[i])
//	{
//		printf("%s\n", arr[i]);
//		i++;
//	}
	absolute = ret_absolute("/usr/bin/ls");
//	if (absolute)
//		printf("1: %s\n", absolute);
//	else
//	{
//		relative = ret_builtabsolute("ls", arr);
//		if (relative)
//			printf("2: %s\n", relative);
//	}
	decider(p, arr);
	free(env);
	return (0);
}

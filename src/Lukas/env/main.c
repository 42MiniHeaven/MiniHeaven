/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/24 20:54:34 by lwittwer         ###   ########.fr       */
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
	char	*in;

	create_env(&data.env, envp);
	data.envp = env_to_envp(data.env);
	if (!data.envp)
		return (free_linked(data.env), 1);
	while (1)
	{
		in = readline("MiniHeaven> ");
		if (!in)
		{
			free(in);
			exit(0);
		}
		if (ft_strncmp(in, "env", ft_strlen(in)) == 0)
		{
			builtin_env(data, in);
			add_history(in);
		}
		if (ft_strncmp(in, "export", 6) == 0)
		{
			builtin_export(data, in);
			add_history(in);
		}
		if (ft_strncmp(in, "unset", 5) == 0)
		{
			builtin_unset(data, in);
			add_history(in);
		}
		free(in);
	}
	free_arr(data.envp);
	free_linked(data.env);
	return (0);
}

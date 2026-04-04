/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:19:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/04 13:42:05 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

void	loop(t_shell *data)
{
	while (1)
	{
		reset_shell(data);
		handle_signals_prompt();
		data->input = readline("miniheaven> ");
		if (!data->input || ft_strcmp(data->input, "exit") == 0)
			break ;
		if (g_signal_status != 0)
			set_exit_code(data);
		if (data->input)
		{
			if (ft_strlen(data->input) > 0)
				add_history(data->input);
			tokeniser(data, data->input);
		}
		parser(data);
		expand_commands(data);
		execute(data);
		printf("%i\n", data->last_exit);
		free_loop(data);
	}
	if (data->input)
		free(data->input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:19:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/30 22:53:12 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniheaven.h"

void	loop(t_shell *data)
{
	while (1)
	{
		reset_shell(data);
	//	handle_signals();
		data->input = readline("miniheaven> ");
		if (!data->input || ft_strcmp(data->input, "exit") == 0)
			break ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:19:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/28 15:01:09 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniheaven.h"

void	loop(t_shell *data)
{
	char	*input;

	reset_shell(data);
//	handle_signals();
	input = readline("miniheaven> ");
	if (!input || ft_strcmp(input, "exit") == 0)
		return (free(input), free_loop(data));
	if (input)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		tokeniser(data, input);
	}
//	fake_cmd(&data->cmds);
	parser(data);
	expand_commands(data);
	execute(data);
//	restore_std_fds(data->fds);
	printf("%d\n", data->last_exit);
	if (!data->should_exit)
		return (free(input), free_loop(data));
	free(input);
	free_loop(data);
	loop(data);
}

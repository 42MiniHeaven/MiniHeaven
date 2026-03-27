/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:19:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 14:51:43 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

void	loop(t_shell *data)
{
	char	*input;

	reset_shell(data);
//	handle_signals();
	input = readline("miniheaven> ");
	if (!input || ft_strcmp(input, "exit") == 0)
		return (free(input));
	if (input)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		lexer(data, input);
	}
//	fake_cmd(&data->cmds);
	data->cmds = parse(data->tokens);
	expand_commands(data);
	execute(data);
	printf("%d\n", data->last_exit);
	free(input);
	free_loop(data);
	loop(data);
}

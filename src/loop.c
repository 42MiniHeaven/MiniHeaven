/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:19:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/19 12:22:18 by lwittwer         ###   ########.fr       */
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
	execute(data);
	printf("%d\n", data->last_exit);
	free(input);
	free_loop(data);
//	loop(data);
}

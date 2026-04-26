/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:02:30 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/26 17:29:11 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

void	reset_shell(t_shell *data)
{
	data->input = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->should_exit = 0;
	data->fds = NULL;
	data->envp = NULL;
	data->path = NULL;
}

void	free_loop(t_shell *data)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->input)
		free(data->input);
	if (data->envp)
		free_arr(data->envp);
	if (data->path)
		free(data->path);
}

static int	process_input(t_shell *data)
{
	if (!data->input)
		return (0);
	if (g_signal_status != 0)
		set_exit_code(data);
	if (*data->input)
		add_history(data->input);
	tokeniser(data, data->input);
	return (1);
}

static int	parse_and_prepare(t_shell *data)
{
	if (parser(data) != 0)
	{
		data->last_exit = 2;
		return (-1);
	}
	if (prepare_heredocs(data, data->cmds) < 0)
		return (-1);
	return (0);
}

void	loop(t_shell *data)
{
	while (1)
	{
		reset_shell(data);
		handle_signals_prompt();
		data->input = readline("miniheaven> ");
		if (!process_input(data))
		{	
			write(1, "exit\n", 5);
			break ;
		}
		if (parse_and_prepare(data) < 0)
		{
			free_loop(data);
			continue ;
		}
		expand_commands(data);
		execute(data);
		free_loop(data);
		if (data->should_exit)
			break ;
	}
}

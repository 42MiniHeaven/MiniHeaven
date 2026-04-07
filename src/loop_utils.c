/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:24:46 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/07 17:57:29 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

//i assume last exit should be kept for echo #?

void	reset_shell(t_shell *data)
{
	data->input = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->should_exit = 0;
}

//maybe restore std fds just in case?!

void	free_loop(t_shell *data)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->input)
		free(data->input);
	close_all_fds();
}

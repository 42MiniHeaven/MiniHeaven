/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:24:46 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/15 18:57:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

//i assume last exit should be kept for echo #?

void	reset_shell(t_shell *data)
{
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/18 15:51:09 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	execute(t_shell *data)
{
	if (!data || !data->cmds)
		return (0);
	if (data->cmds->argv && data->cmds->argv[0]
		&& (ft_strcmp(data->cmds->argv[0], "exit") == 0)
		&& data->cmds->next == NULL)
		data->should_exit = 1;
	if (!data->cmds->next)
		return (exec_single(data));
	return (exec_pipe(data));
}

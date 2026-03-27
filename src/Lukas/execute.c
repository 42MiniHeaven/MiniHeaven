/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/26 22:43:18 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	execute(t_shell *data)
{
	if (!data->cmds || !data->cmds->argv[0])
		return (0);
	if (ft_strcmp(data->cmds->argv[0], "exit") && data->cmds->next == NULL)
		data->should_exit = 1;
	if (handle_all_heredocs(data->cmds) != 0)
	{
		data->last_exit = 1;
		return (0);
	}
	if (!data->cmds->next)
		return (exec_single(data));
	return (exec_pipe(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/06 19:33:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	execute(t_shell *data)
{
	if (!data || !data->cmds)
		return (0);
	if (data->cmds->argv && ft_strcmp(data->cmds->argv[0], "exit") && data->cmds->next == NULL)
		data->should_exit = 1;
	if (!data->cmds->next)
		return (exec_single(data));
	return (exec_pipe(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:14:58 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/26 17:15:09 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"
#include "builtins/builtins.h"

int	dispatcher(t_shell *data)
{
	int	exec_result;

	if (!data->cmds || !data->cmds->argv[0])
		return (0);
	if (handle_all_heredocs(data->cmds) != 0)
	{
		data->last_exit = 1;
		return (0);
	}
	if (!data->cmds->next)
		exec_result = exec_single(data->cmds, data->lst, data->fds, &data->last_exit, &data->should_exit);
	else
	{
		exec_pipe(data->cmds, data->lst, &data->last_exit);
		exec_result = EXEC_OK;
	}
	if (exec_result == EXEC_EXIT_REQUEST)
		data->should_exit = 1;
	return (0);
}

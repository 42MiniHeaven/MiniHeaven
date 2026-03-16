/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/16 16:04:32 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static int	ft_is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
int	exec_single(t_shell *data)
{
	if (!data || !data->cmds || !data->cmds->argv || !data->cmds->argv[0])
		return (0);
	if (ft_is_builtin(data->cmds->argv[0]))
		data->last_exit = exec_builtin(data);
	else
		exec_external(data);
	return (0);
}

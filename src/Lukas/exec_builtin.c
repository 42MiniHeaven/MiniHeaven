/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:08:59 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/16 16:30:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_builtin(t_shell *data)
{
	(void)data;
	if (!data || !data->cmds || !data->cmds->argv || !data->cmds->argv[0])
		return (0);
	if (ft_strcmp(data->cmds->argv[0], "cd") == 0)
		return (builtin_cd(data->cmds, data->list->head));
//	if (ft_strcmp(cmds->argv[0], "echo") == 0)
//		return (builtin_echo(data->cmds, data->list->head));
//	if (ft_strcmp(cmds->argv[0], "env") == 0)
//		return (builtin_env(data->cmds, data->list->head));
	if (ft_strcmp(data->cmds->argv[0], "exit") == 0)
		return (128); //should_exit
//	if (ft_strcmp(cmds->argv[0], "export") == 0)
//		return (builtin_export(data->cmds, data->list->head));
//	if (ft_strcmp(cmds->argv[0], "pwd") == 0)
//		return (builtin_pwd(data->cmds, data->list->head));
//	if (ft_strcmp(cmds->argv[0], "unset") == 0)
//		return (builtin_unset(data->cmds, data->list->head));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:08:59 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 17:32:12 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	exec_builtin(t_shell *data)
{
	if (setup_redirections(data->cmds->redir) == -1)
		return (1);
	if (!data || !data->cmds || !data->cmds->argv || !data->cmds->argv[0])
		return (0);
	if (ft_strcmp(data->cmds->argv[0], "cd") == 0)
		return (builtin_cd(data->cmds, data->list));
	if (ft_strcmp(data->cmds->argv[0], "echo") == 0)
		return (builtin_echo(data->cmds, data->list));
	if (ft_strcmp(data->cmds->argv[0], "env") == 0)
		return (builtin_env(data->cmds, data->list));
	if (ft_strcmp(data->cmds->argv[0], "exit") == 0)
		return (builtin_exit(data->cmds, data));
	if (ft_strcmp(data->cmds->argv[0], "export") == 0)
		return (builtin_export(data->cmds, data->list));
	if (ft_strcmp(data->cmds->argv[0], "pwd") == 0)
		return (builtin_pwd(data->cmds, data->list));
	if (ft_strcmp(data->cmds->argv[0], "unset") == 0)
		return (builtin_unset(data->cmds, data->list));
	return (0);
}

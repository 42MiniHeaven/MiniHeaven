/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:34:46 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/24 14:44:40 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_builtin(t_cmd *cmds, t_env *env)
{
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return (BUILTIN_NOT_FOUND);
	if (!ft_strcmp(cmds->argv[0], "cd"))
		return (builtin_cd(cmds, &env));
	if (!ft_strcmp(cmds->argv[0], "echo"))
		return (builtin_echo(cmds, &env));
	if (!ft_strcmp(cmds->argv[0], "env"))
		return (builtin_env(cmds, &env));
	if (!ft_strcmp(cmds->argv[0], "exit"))
		return (BUILTIN_EXIT);
	if (!ft_strcmp(cmds->argv[0], "export"))
		return (builtin_export(cmds, &env));
	if (!ft_strcmp(cmds->argv[0], "pwd"))
		return (builtin_pwd(cmds, &env));
	if (!ft_strcmp(cmds->argv[0], "unset"))
		return (builtin_unset(cmds, &env));
	return (BUILTIN_NOT_FOUND);
}

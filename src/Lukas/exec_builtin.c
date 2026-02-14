/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:18:08 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 20:37:37 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	exec_builtin(t_cmd *cmds, t_env *env)
{
	int	len = ft_strlen(cmds->argv[0]);
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return (0);
	if (!ft_strncmp(cmds->argv[0], "cd", len))
		return (builtin_cd(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "echo", len))
		return (builtin_echo(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "env", len))
		return (builtin_env(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "exit", len))
		return (builtin_exit(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "export", len))
		return (builtin_export(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "pwd", len))
		return (builtin_pwd(cmds, &env));
	if (!ft_strncmp(cmds->argv[0], "unset", len))
		return (builtin_unset(cmds, &env));
	return (1);
}

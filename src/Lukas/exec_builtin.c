/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:18:08 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/05 20:41:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	exec_builtin(t_mh *mh)
{
	int	len = ft_strlen(mh->cmds.argv[0]);
	if (!mh || !mh->cmds.argv || !mh->cmds.argv[0])
		return (0);
	if (!ft_strncmp(mh->cmds.argv[0], "cd", len))
		return (builtin_cd(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "echo", len))
		return (builtin_echo(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "env", len))
		return (builtin_env(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "exit", len))
		return (builtin_exit(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "export", len))
		return (builtin_export(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "pwd", len))
		return (builtin_pwd(mh, mh->cmds.argv));
	if (!ft_strncmp(mh->cmds.argv[0], "unset", len))
		return (builtin_unset(mh, mh->cmds.argv));
	return (1);
}

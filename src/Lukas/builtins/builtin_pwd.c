/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:39:35 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/17 16:49:51 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../include/miniheaven.h"
/*
int	builtin_pwd(t_cmd *cmd, t_env *env)
{
	char	*cwd;

	(void)cmd;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (0);
}
*/
int	builtin_pwd(t_cmd *cmd, t_env *env)
{
	char	*cwd;

	(void)cmd;
	cwd = get_env_value(env_find(env, "PWD"), "PWD");
	if (!cwd)
		return (0);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}

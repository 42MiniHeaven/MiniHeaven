/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:58:16 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:23:25 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../include/miniheaven.h"

int	builtin_pwd(t_cmd *cmd, t_env **env)
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

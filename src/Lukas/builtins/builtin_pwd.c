/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:58:16 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/05 19:04:37 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../../include/execute.h"

int	builtin_pwd(t_mh *mh, char **argv)
{
	char	*cwd;

	(void)argv;
	(void)mh;
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

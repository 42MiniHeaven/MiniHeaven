/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:30:17 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:21:20 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if(ft_strchr(cmd,'/'))
		return (cmd);	//better check later
	path = get_env_value("PATH", env);
	if (!path)
		return (cmd);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		full = ft_strjoin_char(dirs[i], cmd, '/');
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (cmd);
}

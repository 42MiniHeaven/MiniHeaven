/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:41:29 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/15 15:42:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path = get_env_value("PATH", env);
	if (!path)
		return (cmd);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (cmd);
	i = 0;
	while (dirs[i])
	{
		full = ft_strjoin_char(dirs[i], cmd, '/');
		if (access(full, X_OK) == 0)
			return (free_arr(dirs), full);
		free(full);
		i++;
	}
	free_arr(dirs);
	return (cmd);
}

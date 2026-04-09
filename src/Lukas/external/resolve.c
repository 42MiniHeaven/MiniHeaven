/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:41:29 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 17:35:00 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(env, "PATH");
	if (!path)
		return (ft_strdup(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		return (ft_strdup(cmd));
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
	return (NULL);
}

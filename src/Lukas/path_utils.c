/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:14:34 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/13 14:33:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//File usage: Utility functions to find and build the environment

//Description: returns PATH from environment "envp"
//				-needed to lookup external commands

char	*ret_unresolved(char **envp)
{
	int		i;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0) //use ft_strncmp
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

//Description: Helperfunction: returns a string from env

static char	*ret_pathstr(char *env)
{
	char	*str;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != ':')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = -1;
	while (++j < i)
		str[j] = env[j];
	str[j] = '\0';
	return (str);
}

//Description: Helperfunction: returns size for allocation of path arr

static int	ret_pathsize(char *env)
{
	int	size;
	int	i;

	if (!env)
		return (0);
	i = -1;
	size = 0;
	while (env[++i])
	{
		if (env[i] == ':')
			size++;
	}
	return (size);
}

//Description: returns 2 dimensional array of the Path
//				-needed to build the environment for the external command

char	**ret_patharr(char *env)
{
	int		i;
	char	**path;
	int		size;
	int		j;

	if (!env)
		return (NULL);
	size = ret_pathsize(env);
	if (size == 0)
		return (NULL);
	path = malloc((size + 1) * sizeof(char *));
	if (!path)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < size)
	{
		path[i] = ret_pathstr(&env[j]);
		while (env[j] && env[j] != ':')
			j++;
		j++;
	}
	path[i] = 0;
	return (path);
}

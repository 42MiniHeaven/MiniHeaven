/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:28:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/22 17:22:43 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static char	*get_shell_path(void)
{
	char	buf[4096];
	char	*ret;
	ssize_t	len;

	len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
	if (len == -1)
	{
		perror("readlink");
		return (NULL);
	}
	buf[len] = '\0';
	ret = ft_strjoin("_=", buf);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*get_pwd(void)
{
	char	*cwd;
	char	*ret;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	ret = ft_strjoin("PWD=", cwd);
	if (!ret)
		return (NULL);
	free(cwd);
	return (ret);
}

static char *get_shlvl(int shlvl)
{
	char	*tmp;
	char	*ret;

	if (!shlvl)
		return (NULL);
	tmp = ft_itoa(shlvl);
	ret = ft_strjoin("SHLVL=", tmp);
	if (!ret)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (ret);
}

char	**empty_env(void)
{
	char	**env;
	int		shlvl;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	shlvl = 1;
	env[0] = get_pwd();
	env[1] = get_shlvl(shlvl);
	env[2] = get_shell_path();
	env[3] = NULL;
	return (env);
}


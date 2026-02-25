/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_empty_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:05:24 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 13:26:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

static char	*get_shell_path(void)
{
	char	buf[4096];
	ssize_t	len;

	len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
	if (len == -1)
	{
		perror("readlink");
		return (NULL);
	}
	buf[len] = '\0';
	return (ft_strdup(buf));
}

static char	*get_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

void	init_empty_env(t_env **lst)
{
	char	**env;
	char	*shlvl_str;
	int		shlvl;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return ;
	shlvl_str = get_env_value("SHLVL", *lst);
	shlvl = 0;
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str);
	env[0] = ft_strjoin("PWD=", get_pwd());
	env[1] = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	env[2] = ft_strjoin("_=", get_shell_path());
	env[3] = NULL;
	create_env_list(lst, env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 20:37:17 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"
#include "env/env.h"

static char	*get_shell_path()
{
	char	buf[4096];
	ssize_t	len;

	len = readlink("/proc/self/exe", buf, sizeof(buf)-1);
	if (len == -1)
	{
		perror("readlink");
		return (NULL);
	}
	buf[len] = '\0';
	return (ft_strdup(buf));
}

static char	*get_pwd()
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return NULL;
	}
	return (cwd);
}

static void	env_i(t_env **llist)
{
	char	**env;
	char	*shlvl_str;
	int		shlvl;

	env = malloc (sizeof(char *) * 4);
	if (!env)
		return ;
	shlvl_str = get_env_value("SHLVL", *llist);
	shlvl = 1;
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	env[0] = ft_strjoin("PWD=", get_pwd());
	env[1] = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	env[2] = ft_strjoin("_=", get_shell_path());
	env[3] = NULL;
	create_env_list(llist, env);
}

void	init_shell(t_shell *data, char **envp)
{
	if (envp[0] != NULL)
		create_env_list(&data->llist, envp);
	else
		env_i(&data->llist);
	safe_std_fds(data);
}

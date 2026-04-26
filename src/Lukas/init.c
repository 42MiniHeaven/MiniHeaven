/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/26 14:39:15 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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

static void	env_i(t_env **llist)
{
	char	**env;
	char	*shlvl_str;
	int		shlvl;

	env = malloc (sizeof(char *) * 4);
	if (!env)
		return ;
	shlvl_str = get_env_value("SHLVL", *llist);
	shlvl = 0;
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str);
	env[0] = ft_strjoin("PWD=", get_pwd());
	env[1] = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	env[2] = ft_strjoin("_=", ft_strdup(""));
	env[3] = NULL;
	create_env_list(llist, env);
}

void	init_shell(t_shell *data, char **envp)
{
	if (envp[0] != NULL)
		create_env_list(&data->list, envp);
	else
		env_i(&data->list);
	safe_std_fds(data);
}

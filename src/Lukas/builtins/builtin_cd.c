/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:35:08 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 15:22:20 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/miniheaven.h"

static char *get_cd_target(char **args, t_env *env)
{
	if (!args[1] || (ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0))
		return (get_env_value("HOME", env));
	if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
		return (get_env_value("OLDPWD", env));
	return (args[1]);
}

static void	update_pwd_oldpwd(t_env *env, char *oldpwd)
{
	char *newpwd;

	newpwd = getcwd(NULL, 0);
	env_set(env_find(env, "OLDPWD"), 1, oldpwd);
	env_set(env_find(env, "PWD"), 1 ,newpwd);
	free(newpwd);
}

static int	cd_error(const char *message, const char *path)
{

	if (path)
		fprintf(stderr, "minishell: cd: %s: %s\n", path, message);
	else
		fprintf(stderr, "minishell: cd: %s\n", message);
	return (1);
}

int	builtin_cd(t_cmd *cmd, t_env **env)
{
	char	*target;
	char	*oldpwd;

	if (cmd->argv[1] && cmd->argv[2])
		return (cd_error("too many arguments", NULL));
	target = get_cd_target(cmd->argv, *env);
	if (!target)
		return (cd_error("HOME not set", NULL)); //check later
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	update_pwd_oldpwd(*env, oldpwd);
	free(oldpwd);
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-", ft_strlen(cmd->argv[1])) == 0)
		printf("%s\n", get_env_value("PWD", *env));
	return (0);
}

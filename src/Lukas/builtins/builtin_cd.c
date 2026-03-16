/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:13:40 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/16 16:32:04 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniheaven.h"
#include "../env/env.h"

static char	*get_cd_target(char **args, t_env *env)
{
	if (!args[1] || (ft_strcmp(args[1], "~") == 0))
		return (get_env_value(env, "HOME"));
	if (ft_strcmp(args[1], "-") == 0)
		return (get_env_value(env, "OLDPWD"));
	return (args[1]);
}

static void	update_pwd_oldpwd(t_env *env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	env_update(env_find(env, "OLDPWD"), oldpwd);
	env_update(env_find(env, "PWD"), newpwd);
	free(newpwd);
}

static int	cd_error(const char *message, const char *path)
{
	if (path)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "minishell: cd: ", 15);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	return (1);
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*target;
	char	*oldpwd;

	if (cmd->argv[1] && cmd->argv[2])
		return (cd_error("too many arguments", NULL));
	target = get_cd_target(cmd->argv, env);
	if (!target)
		return (cd_error("HOME not set", NULL));
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	update_pwd_oldpwd(env, oldpwd);
	free(oldpwd);
	if (cmd->argv[1]
		&& ft_strcmp(cmd->argv[1], "-") == 0)
		printf("%s\n", get_env_value(env, "PWD"));
	return (0);
}

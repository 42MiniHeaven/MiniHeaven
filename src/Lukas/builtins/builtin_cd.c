/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:13:40 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 21:56:53 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	update_pwd_oldpwd(t_env *env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	env_update(env_find(env, "OLDPWD"), oldpwd);
	env_update(env_find(env, "PWD"), newpwd);
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

static char	*get_cd_target(char **args, t_env *env)
{
	if (!args[1] || (ft_strcmp(args[1], "~") == 0))
		return (get_env_value(env, "HOME"));
	return (args[1]);
}

int	builtin_cd(t_cmd *cmd, t_environment *list)
{
	char	*target;
	char	*oldpwd;

	if (cmd->argv[1] && cmd->argv[2])
		return (cd_error("too many arguments", NULL));
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-") == 0)
		return (cd_error("switch to OLDPWD in the future", "- not implemented"));
	target = get_cd_target(cmd->argv, list->head);
	if (!target)
		return (cd_error("HOME not set", NULL));
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	update_pwd_oldpwd(list->head, oldpwd);
	free(oldpwd);
	if (cmd->argv[1]
		&& ft_strcmp(cmd->argv[1], "-") == 0)
		printf("%s\n", get_env_value(list->head, "PWD"));
	return (0);
}

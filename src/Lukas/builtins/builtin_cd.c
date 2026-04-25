/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:13:40 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/25 15:50:31 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	update_pwd_oldpwd(t_env *env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return ;
	if (env && oldpwd && env_find(env, "OLDPWD"))
		env_update(env_find(env, "OLDPWD"), oldpwd);
	if (env && env_find(env, "PWD"))
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

static char	*get_cd_target(char **args, t_env *env)
{
	if (!args[1] || (ft_strcmp(args[1], "~") == 0))
		return (get_env_value(env, "HOME"));
	return (args[1]);
}

static int	handle_cd_dash(t_environment *list)
{
	char	*oldpwd;
	char	*tmp_oldpwd;

	oldpwd = get_env_value(list->head, "OLDPWD");
	if (!oldpwd)
		return (cd_error("OLDPWD not set", NULL), 1);
	tmp_oldpwd = ft_strdup(oldpwd);
	if (!tmp_oldpwd)
		return (ft_error("malloc failed for oldpwd", NULL, 2), 1);
	if (chdir(oldpwd) != 0)
	{
		perror("minishell: cd");
		free(tmp_oldpwd);
		return (1);
	}
	else
		printf("%s\n", tmp_oldpwd);
	if (list->head)
		update_pwd_oldpwd(list->head, tmp_oldpwd);
	free(tmp_oldpwd);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_environment *list)
{
	char	*target;
	char	*oldpwd;

	if (cmd->argv[1] && cmd->argv[2])
		return (cd_error("too many arguments", NULL));
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-") == 0)
		return (handle_cd_dash(list));
	target = get_cd_target(cmd->argv, list->head);
	if (!target)
		return (cd_error("HOME not set", NULL));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("minishell: cd: error retrieving current \
		directory: getcwd: "), 1);
	if (chdir(target) != 0)
		return (cd_error(strerror(errno), target), free(oldpwd), 1);
	if (list->head)
		update_pwd_oldpwd(list->head, oldpwd);
	free(oldpwd);
	if (cmd->argv[1]
		&& ft_strcmp(cmd->argv[1], "-") == 0)
		printf("%s\n", get_env_value(list->head, "PWD"));
	return (0);
}

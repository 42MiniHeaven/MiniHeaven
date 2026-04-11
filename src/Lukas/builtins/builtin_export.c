/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:43:52 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 01:19:42 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

static void	print_export(char **env, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
	i = -1;
	while (env[++i] && ft_strcmp(env[i], "_") && i < n - 1)
		printf("declare -x %s\n", env[i]);
}

static int	export_update_env(t_environment *list, char *str)
{
	char	*key;
	char	*value;

	key = get_key(str);
	value = get_value(str);
	if (env_find(list->head, key))
	{
		env_update(env_find(list->head, key), value);
		free(key);
		free(value);
	}
	else
		env_add(list, env_create_node(key, value));
	return (0);
}

int	builtin_export(t_cmd *cmd, t_environment *list)
{
	int		i;
	char	**env;

	i = 1;
	if (!cmd->argv[i])
	{
		if (!ft_strcmp(cmd->argv[0], "export"))
		{
			env = env_arr(list->head);
			print_export(env, arr_len(env));
			free_arr(env);
			return (0);
		}
	}
	while (cmd->argv[i])
	{
		export_update_env(list, cmd->argv[i]);
		i++;
	}
	return (0);
}

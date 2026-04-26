/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 09:43:52 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/26 17:17:12 by lwittwer         ###   ########.fr       */
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
	while (env[++i] && i < n)
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
			continue ;
		printf("declare -x %s\n", env[i]);
	}
}

static int	valid_export(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	if (s[i] && (ft_isalpha(s[i]) || s[i] == '_'))
	{
		while (s[i] && s[i] != '=' && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		if (s[i] == '\0' || s[i] == '=')
			return (0);
		return (1);
	}
	return (1);
}

int	export_update_env(t_environment *list, char *str)
{
	char	*key;
	char	*value;

	if (valid_export(str))
	{
		ft_err_export_three("export: `", str, "not a valid identifier");
		return (1);
	}
	key = get_key(str);
	if (!key)
	{
		ft_err_export_three("export: `", str, "not a valid identifier");
		return (1);
	}
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
			env = env_arr_export(list->head);
			print_export(env, arr_len(env));
			return (free_arr(env), 0);
		}
	}
	while (cmd->argv[i])
	{
		if (ft_strlen(cmd->argv[i]) > 65536)
		{
			handle_export_overflow(list, cmd->argv[i]);
			return (ft_error("export: ", "malloc failed", 2), 1);
		}
		if (export_update_env(list, cmd->argv[i]))
			return (1);
		i++;
	}
	return (0);
}

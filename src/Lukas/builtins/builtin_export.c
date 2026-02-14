/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:10:35 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 21:25:06 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/miniheaven.h"

/**
 * @brief   Export allows to add to env list.
 *
 * export on its own prints the environment list in alphabetical order.
 * with an argument export adds it to the env list
 *
 * @param   data	Struct containing env list and envp
 * @param   cmd		Input string containing export and potential flags
 */


static int	print_sorted(char **arr, int n)
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
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j])) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	return (0);
}

static	int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	if (!env)
		return (0);
	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	return (i);
}

static int	export_check(t_env *env, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i - 1);
	if (!key)
		return (1);
	value = ft_substr(str, i + 1, ft_strlen(str) - (i + 1) );
	if (!value)
		return (free(key), 1);
	if (!env_find(env, key))
		env_set(env, 2, str);
	else
		env_set(env_find(env, key), 1, value);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int		i;
	int		size;
	int		status;

	status = 0;
	i = 1;
	if (!cmd->argv[i])
	{
		if (ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) == 0)
		{
			size = env_size(*env);
			return (print_sorted(llist_to_env(*env),size));
		}
	}
	while (cmd->argv[i])
	{
		if (export_check(*env, cmd->argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

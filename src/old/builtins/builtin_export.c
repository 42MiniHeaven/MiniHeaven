/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:26:54 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/13 19:32:00 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../include/miniheaven.h"

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

/**
 * @brief   Export allows to add to env list.
 *
 * export on its own prints the environment list in alphabetical order.
 * with an argument export adds it to the env list
 *
 * @param   data	Struct containing env list and envp
 * @param   cmd		Input string containing export and potential flags
 */

static void	print_sorted(char **arr)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	n = arr_len(arr);
	if (n < 2)
		return ;
	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	i = -1;
	while (arr[++i] && ft_strncmp(arr[i], "_", 1) && i < n - 1)
		printf("declare -x %s\n", arr[i]);
}

static int	export_check(t_env **env, char *str)
{
	char	*key;
	char	*value;

	key = get_key(str);
	value = get_value(str);
	if (env_find(*env, key))
		update_env(env_find(*env, key), value);
	else
		add_back(env, str);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	if (!cmd->argv[i])
	{
		if (!ft_strcmp(cmd->argv[0], "export"))
			return (print_sorted(lst_to_env(*env)), 0);
	}
	while (cmd->argv[i])
	{
		if (export_check(env, cmd->argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:10:35 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 17:13:15 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../../../include/execute.h"

/**
 * @brief   Export allows to add to env list.
 *
 * export on its own prints the environment list in alphabetical order.
 * with an argument export adds it to the env list
 *
 * @param   data	Struct containing env list and envp
 * @param   cmd		Input string containing export and potential flags
 */


static void	print_sorted(char **arr, int n)
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
			if (strcmp(arr[j], arr[j + 1]) > 0)
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

static int	export_check(t_mh *mh, char *cmd1, char *cmd2)
{
	int		s;
	int		e;
	char	*test;
	char	*cmd;

	cmd = ft_strjoin_char(cmd1, cmd2, '=');
	if (!cmd)
		return (1);
	e = 0;
	while (cmd[e] && cmd[e] != '=')
		e++;
	s = 0;
	while (cmd[s] && cmd[s] != ' ')
		s++;
	s++;
	test = ft_substr(cmd, s, e - s);
	if (!env_find(mh->llist, test))
		env_set(mh->llist, 2, cmd);
	else
		env_set(env_find(mh->llist, test), 1, cmd + e + 1);
	free(cmd);
	return (0);
}

int	builtin_export(t_mh *mh, char **argv)
{
	char	**split;
	int		i;
	int		size;
	int		status;

	status = 0;
	split = ft_split(argv[0], ' ');
	if (!split)
		return (1);
	i = 1;
	if (!split[i])
	{
		if (ft_strncmp(argv[0], "export", ft_strlen(split[0])) == 0)
		{
			mh->env = llist_to_env(mh->llist);
			size = env_size(mh->llist);
			print_sorted(mh->env, size);
		}
	}
	while (split[i])
	{
		if (export_check(mh, split[0], split[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

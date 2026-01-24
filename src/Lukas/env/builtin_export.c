/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:10:35 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/24 20:51:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"

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

void	builtin_export(t_exec data, char *cmd)
{
	int		s;
	int		e;
	char	*test;
	int		size;

	e = 0;
	while (cmd[e] && cmd[e] != '=')
		e++;
	s = 0;
	while (cmd[s] && cmd[s] != ' ')
		s++;
	s++;
	test = ft_substr(cmd, s, e - s);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
	{
		data.envp = env_to_envp(data.env);
		size = env_size(data.env);
		print_sorted(data.envp, size);
	}
	else if (!env_find(data.env, test))
		env_set(data.env, 2, cmd);
	else
		env_set(env_find(data.env, test), 1, cmd + e + 1);
}

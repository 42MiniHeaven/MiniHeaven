/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:10:35 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/23 17:40:48 by lwittwer         ###   ########.fr       */
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

static void	add_back(t_env *env, char *cmd)
{
	t_env	*tmp;
	size_t	s;
	size_t	n;
	size_t	len;
	size_t	start;

	len = ft_strlen(cmd);
	s = 0;
	while (cmd[s] && cmd[s] != ' ')
		s++;
	s++;
	start = s;
	while (cmd[s] && cmd[s] != '=')
		s++;
	n = s + 1;
	tmp = env_new(ft_substr(cmd, start, s - start), ft_substr(cmd, n, len - n));
	env_add_back(&env, tmp);
}

void	builtin_export(t_exec data, char *cmd)
{
	int		i;
	char	*test;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	test = ft_substr(cmd, 0, i);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
	{
		while (data.envp[i])
			i++;	
		print_sorted(data.envp, i);
	}
	if (!env_find(data.env, test))
	{
		add_back(data.env, cmd);
	}
//	if (env_find)
//		update_key();
	free(test);
}

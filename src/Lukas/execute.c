/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/22 18:18:18 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	update_env_var(t_shell *data)
{
	t_cmd	*tmp;
	char	*update;
	int		i;

	update = NULL;
	tmp = data->cmds;
	while (tmp)
	{
		if (!tmp->argv)
			return ;
		i = 0;
		if (tmp->argv && tmp->argv[i])
		{
			if (is_builtin(tmp->argv[i]) == 0)
			{
				while (tmp->argv[i])
					update = tmp->argv[i++];
			}
			else
				update = tmp->argv[0];
		}
		tmp = tmp->next;
	}
	env_update(env_find(data->list->head, "_"), update);
}

int	execute(t_shell *data)
{
	if (!data || !data->cmds)
		return (0);
	if (data->cmds->argv && data->cmds->argv[0]
		&& (ft_strcmp(data->cmds->argv[0], "exit") == 0)
		&& data->cmds->next == NULL)
		data->should_exit = 1;
	if (!data->cmds->next)
	{
		if (data->cmds && data->cmds->argv[0])
			update_env_var(data);
		return (exec_single(data));
	}
	return (exec_pipe(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/22 18:17:18 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	update_env_var(t_shell *data)
{
	t_cmd	*tmp;
	char	*update;
	char	*path;

	update = NULL;
	tmp = data->cmds;
	while (tmp)
	{
		if (tmp->argv && tmp->argv[0])
			update = tmp->argv[0];
		tmp = tmp->next;
	}
	path = resolve_path(update, data->list->head);
	if (!path)
		path = ft_strdup("");
	env_update(env_find(data->list->head, "_"), path);
	update = NULL;
	free(path);
	path = NULL;
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
		if (data->cmds && data->cmds->argv)
			update_env_var(data);
		return (exec_single(data));
	}
	return (exec_pipe(data));
}

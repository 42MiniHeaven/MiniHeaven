/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/04 17:58:29 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	exec_single(t_shell *data)
{
	if (!data || !data->cmds || !data->cmds->argv || !data->cmds->argv[0])
		return (0);
	if (!is_builtin(data->cmds->argv[0]))
		data->last_exit = exec_builtin(data);
	else
		exec_external(data);
	return (0);
}

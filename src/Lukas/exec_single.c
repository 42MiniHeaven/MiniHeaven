/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:42:41 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/06 19:27:16 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	exec_single(t_shell *data)
{
	if (data->cmds->argv && !is_builtin(data->cmds->argv[0]))
		data->last_exit = exec_builtin(data);
	else
		exec_external(data);
	return (0);
}

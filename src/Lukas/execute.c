/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:10:10 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/15 13:45:48 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

int	execute(t_shell *data)
{
	(void)data;
//	if (!data->cmds)
//		return (0);
	if (!data->cmds->next)
		return (exec_single(data));
//		return (24);
	return (42);//for testing
//	return (exec_pipeline(shell));
}

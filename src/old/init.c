/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:55:36 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/24 22:41:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

void	init_shell(t_shell *data, char **envp)
{
	if (envp[0] != NULL)
		create_env_list(&data->lst, envp);
	else
		init_empty_env(&data->lst);
	safe_std_fds(data);
}

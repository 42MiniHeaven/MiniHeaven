/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:36:39 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/05 14:07:54 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	init_shell(t_mh *data, char **envp)
{
	if (envp[0] != NULL)
	{
		create_env_list(&data->llist, envp);
		data->env = llist_to_env(data->llist);
	}
	else
		printf("SHLVL PWD & _ missing.\n");	//SHLVL PWD & _
}

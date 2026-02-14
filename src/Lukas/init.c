/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:59:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 14:22:46 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	init_shell(t_mh *data, char **envp)
{
	if (envp[0] != NULL)
	{
		create_env_list(&data->llist, envp);
	//	data->env = llist_to_env(data->llist);
	}
	else
		printf("SHLVL PWD & _ missing.\n");	//SHLVL PWD & _
}

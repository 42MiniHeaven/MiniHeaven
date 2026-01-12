/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:55:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/12 21:11:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/exec.h"
#include "executor.h"

int	decider(t_pipeline data, char **envp)
{
	if (data.count == 0)
		return (42); //no command to execute
	if (data.count == 1)
	{
		single(data, envp);
		return (0);
	}
	if (data.count == 2)
		printf("we enter 2\n");
	return (0);
}

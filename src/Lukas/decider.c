/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:55:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/10 21:23:36 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	decider(t_cmd data)
{
	if (data.flag == FORK)
	{
		printf("entered FORK\n");
		return (0);
	}
	if (data.flag == SINGLE)
	{
		single(data);
		return(0);
	}
	if (data.flag == HEREDOC)
	{
		printf("entered HEREDOC\n");
		return (0);
	}
	if (data.flag == REDIRECT)
	{
		printf("entered REDIRECT\n");
		return (0);
	}
	if (data.flag == EMPTY)
	{
		printf("entered EMPTY\n");
		return (0);
	}
	if (data.flag == COUNT)
	{
		printf("entered COUNT\n");
		return (0);
	}
	return (1);
}

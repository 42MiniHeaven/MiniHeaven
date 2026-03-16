/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:18:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/16 16:30:05 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniheaven.h"

void	fake_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**arg;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return ;
	arg = malloc(sizeof(char *) * 3);
	if (!arg)
	{
		free(tmp);
		return ;
	}
	tmp->cmd = NULL;
	arg[0] = ft_strdup("cd");
	arg[1] = ft_strdup("src");
	arg[2] = NULL;
	tmp->argv = arg;
	tmp->redir = NULL;
	tmp->next = NULL;
	*cmd = tmp;
}

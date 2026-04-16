/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 13:18:55 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 18:41:12 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	fake_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**arg;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return ;
	arg = malloc(sizeof(char *) * 2);
	if (!arg)
	{
		free(tmp);
		return ;
	}
	arg[0] = ft_strdup("pwd");
	arg[1] = NULL;
	tmp->argv = arg;
	tmp->redir = NULL;
	tmp->next = NULL;
	*cmd = tmp;
}

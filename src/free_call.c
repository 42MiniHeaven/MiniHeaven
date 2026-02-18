/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:47:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/18 22:15:48 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	free_call(t_shell data, int args, char *input)
{
	if (input)
		free(input);
	if (data.cmds)
		free_cmds(data.cmds);
	if (data.tokens)
		free_tokens(data.tokens);
	if (args == 1)
	{
		free_llist(data.llist);
		free_shell(&data);
	}
}

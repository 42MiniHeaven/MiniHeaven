/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:47:45 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/18 18:17:55 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	free_call(t_shell data, int args, char *input)
{
	if (input)
		free(input);
	if (data.tokens)
		free_struct_tokens(data.tokens);
	if (data.cmds)
		free_struct_cmds(data.cmds);
	if (args == 1)
	{
		free_struct_llist(data.llist);
		free_struct_shell(&data);
	}
}

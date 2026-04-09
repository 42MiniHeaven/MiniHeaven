/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:55:32 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/09 13:10:09 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	parser_exit(t_parser *p)	//TODO: pls check if that is ok for you
{
	if (p->head)
		free_cmds(p->head);
	if (p->current)
		p->current = NULL;
	p->state = 0;
	p->last_redir = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:58:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 19:44:07 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	parser_exit(t_parser *p)
{
	if (p->head)
		free_cmds(p->head);
	if (p->current)
		p->current = NULL;
	p->state = 0;
	p->last_redir = 0;
}

bool	cmd_add_redir(t_cmd *cmd, int type, const char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = redir_new(type, file);
	if (!new)
		return (false);
	if (!cmd->redir)
	{
		cmd->redir = new;
		return (true);
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

bool	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return (true);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

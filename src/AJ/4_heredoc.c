/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:25:23 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 14:24:01 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	free_hdlist(t_hdnode *list)
{
	t_hdnode	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

static void	hd_add_back(t_hdnode **head, t_hdnode **tail, t_redir *redir)
{
	t_hdnode	*new;

	new = ft_calloc(sizeof(t_hdnode), 1); // TODO: protect new
	new->redir = redir;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

static t_hdnode	*collect_heredocs(t_cmd *cmds)
{
	t_hdnode	*head;
	t_hdnode	*tail;
	t_cmd		*tmp;
	t_redir		*r;

	head = NULL;
	tail = NULL;
	tmp = cmds;
	while (tmp)
	{
		r = tmp->redir;
		while (r)
		{
			if (r->type == HEREDOC)
				hd_add_back(&head, &tail, r);
			r = r->next;
		}
		tmp = tmp->next;
	}
	return (head);
}

static int	process_all_heredocs(t_hdnode *list, t_shell *data)
{
	while (list)
	{
		create_heredoc(list->redir, data);
		list = list->next;
	}
	return (0);
}

int	prepare_heredocs(t_shell *data, t_cmd *cmds)
{
	t_hdnode	*list;

	list = collect_heredocs(cmds);
	if (!list)
		return (0);
	if (process_all_heredocs(list, data) < 0)
	{
		free_hdlist(list);
		return (-1);
	}
	free_hdlist(list);
	return (0);
}

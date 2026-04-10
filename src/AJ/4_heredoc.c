/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:25:23 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 19:00:17 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	free_hdlist(t_hdnode *list)
{
	t_hdnode *tmp;

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

	new = malloc(sizeof(t_hdnode));
	new->redir = redir;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}
/*
static int	read_single_heredoc(t_redir *hd, t_shell *data)
{
	int	pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, hd->file) == 0)
		{
			free(line);
			break;
		}
		if (hd->expand)
		{
			expanded = expand_line(data, line);
			free(line);
			line = expanded;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
*/
static t_hdnode	*collect_heredocs(t_cmd *cmds)
{
	t_hdnode	*head = NULL;
	t_hdnode	*tail = NULL;
	t_cmd		*tmp;
	t_redir		*r;

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
	int	fd;

	while (list)
	{
		//fd = read_single_heredoc(list->redir, data);
		fd = create_heredoc(list->redir, data);
		if (fd < 0)
			return (-1);
		list->redir->fd = fd;
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

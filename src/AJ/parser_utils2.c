/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*   Created: 2026/03/26 16:58:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/26 17:02:49 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	cmd_add_redir(t_cmd *cmd, int type, const char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = redir_new(type, file);
	if (!new)
		return (0);
	if (!cmd->redir)
	{
		cmd->redir = new;
		return (1);
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	syntax_error(char *msg)
{
	ft_putstr_fd("Syntax error: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

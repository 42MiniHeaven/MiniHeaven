/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:58:51 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 15:49:32 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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

int	syntax_error(char *type)
{
	char	*msg_part;
	char	*msg_final;

	// ft_putstr_fd("Minishell: ", 2);
	msg_part = ft_strjoin("syntax error near unexpected token `", type);
	msg_final = ft_strjoin(msg_part, "'");
	ft_putendl_fd(msg_final, 2);
	free(msg_part);
	free(msg_final);
	return (-1);
}

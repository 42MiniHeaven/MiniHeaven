/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:09 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/18 22:15:21 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	free_tokens(t_token *lst)
{
	t_token	*next;

	while (lst)
	{
		next = lst->next;
		if (lst->value)
			free(lst->value);
		lst->type = 0;
		if (lst)
			free(lst);
		lst = next;
	}
}

static void	free_redir(t_redir *lst)
{
	t_redir	*next;

	while (lst)
	{
		next = lst->next;
		lst->type = 0;
		free(lst->file);
		close(lst->fd);
		free(lst);
		lst = next;
	}
}

void	free_cmds(t_cmd *lst)
{
	t_cmd	*next;

	while (lst)
	{
		next = lst->next;
		if (lst->argv)
		{
			free(lst->argv);
			lst->argv = NULL;
		}
		free_redir(lst->redir);
		if (lst)
			free(lst);
		lst = next;
	}
}

void	free_llist(t_env *lst)
{
	t_env	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->key);
		free(lst->value);
		lst->is_exported = 0;
		free(lst);
		lst = next;
	}
}

void	free_shell(t_shell *data)
{
	restore_std_fds(data->fds);
	free(data);
}

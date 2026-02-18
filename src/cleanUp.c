/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:09 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/18 20:01:58 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

void	free_struct_tokens(t_token *lst)
{
	t_token	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->value);
		lst->type = 0;
		free(lst);
		lst = next;
	}
}

static void	free_struct_redir(t_redir *lst)
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

void	free_struct_cmds(t_cmd *lst)
{
	t_cmd	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->cmd);
		free_arr(lst->argv);
		free_struct_redir(lst->redir);
		free(lst);
		lst = next;
	}
}

void	free_struct_llist(t_env *lst)
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

void	free_struct_shell(t_shell *data)
{
	restore_std_fds(data->fds);
	free(data);
}

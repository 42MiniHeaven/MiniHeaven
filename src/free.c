/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:05:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/17 18:05:12 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		head->type = 0;
		free(head);
		head = next;
	}
}

static void	free_redirs(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		head->type = 0;
		if (head->file)
		{
			free(head->file);
			head->file = NULL;
		}
		if (head->tmp_file)
		{
			free(head->tmp_file);
			head->tmp_file = NULL;
		}
		if (head->fd != -1)
		{
			wclose(head->fd);
			head->fd = -1;
		}
		free(head);
		head = next;
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		if (head->argv)
		{
			free_arr(head->argv);
			head->argv = NULL;
		}
		if (head->redir)
		{
			free_redirs(head->redir);
			head->redir = NULL;
		}
		free(head);
		head = next;
	}
	next = NULL;
}

void	free_environment(t_environment *list)
{
	t_env	*curr;
	t_env	*tmp;

	if (!list)
		return ;
	curr = list->head;
	while (curr)
	{
		tmp = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
	free(list);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
	}
	free(arr);
}

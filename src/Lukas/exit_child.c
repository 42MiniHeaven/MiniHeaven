/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:31:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/13 17:55:17 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

static void	child_output(char *error, char *msg)
{
	if (error)
		write(2, error, ft_strlen(error));
	if (msg)
		write(2, msg, ft_strlen(msg));
}

static void	free_child(t_shell *data)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->list)
		free_environment(data->list);
	if (data->envp)
		free_arr(data->envp);
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	if (data->input)
		free(data->input);
	if (data->fds)
		close_backup_fds(data->fds);
}

static void	exit_handler(int err)
{
	if (err == ENOENT || err == EFAULT)
		exit(127);
	if (err == EACCES || err == ENOTDIR || err == EISDIR)
		exit(126);
	if (err == ENOEXEC)
		exit(0);
	exit(1);
}

void	exit_child(t_shell *data, int err, char *error, char *msg)
{
	child_output(error, msg);
	free_child(data);
	exit_handler(err);
}

//TODO: Lukas check if you can rename this file and just call it exit to have
// less files
void	parser_exit(t_parser *p)
{
	if (p->head)
		free_cmds(p->head);
	if (p->current)
		p->current = NULL;
	p->state = 0;
	p->last_redir = 0;
}

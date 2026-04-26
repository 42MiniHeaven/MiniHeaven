/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:31:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/26 13:04:13 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	free_child(t_shell *data)
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
	wclose(0);
	wclose(1);
	wclose(2);
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

void	exit_early(t_shell *data, t_cmd *cmds)
{
	int	ret;

	ret = 0;
	if (cmds && cmds->argv[0] && cmds->argv[1]
		&& ft_strcmp(cmds->argv[0], "exit") == 0)
		ret = ft_atoi(cmds->argv[1]);
	free_child(data);
	exit(ret % 256);
}

void	exit_child(t_shell *data, int err, char *error, char *msg)
{
	int	fd;

	if (err == EACCES && error && ft_strcmp(error, "") != 0)
	{
		fd = open(data->path, O_RDONLY | O_DIRECTORY);
		if (fd != -1)
		{
			ft_error(error, ": Is a directory", 2);
			free_child(data);
			exit(126);
		}
		close(fd);
	}
	if (error && ft_strcmp(error, "") == 0)
		err = ENOENT;
	if (error && msg)
		ft_error(error, msg, 2);
	free_child(data);
	exit_handler(err);
}

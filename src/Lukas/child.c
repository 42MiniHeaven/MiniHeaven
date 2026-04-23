/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:39:15 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/23 22:13:16 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

void	exec_builtin_child(t_cmd *cmds, t_shell *data)
{
	int	ret;

	ret = 0;
	handle_signals_exec_child();
	if (!cmds && !cmds->argv[0] && ft_strcmp(cmds->argv[0], "exit") == 0)
		exit_early(data, cmds);
	if (setup_redirections(cmds->redir) == -1)
		return (close_redir_fds(), exit_child(data, errno, NULL, NULL));
	ret = exec_builtin(cmds, data);
	free_child(data);
	exit (ret);
}

void	child(t_cmd *cmds, t_shell *data)
{
	close_all_fds();
	data->envp = NULL;
	data->path = NULL;
	handle_signals_exec_child();
	if (!cmds && !cmds->argv[0] && ft_strcmp(cmds->argv[0], "exit") == 0)
		exit_early(data, cmds);
	if (setup_redirections(cmds->redir) == -1)
		return (close_redir_fds(), exit_child(data, errno, NULL, NULL));
	if (!cmds->argv || cmds->argv[0] == NULL)
		return (close_redir_fds(), exit_child(data, errno, NULL, NULL));
	data->envp = env_arr(data->list->head);
	data->path = resolve_path(cmds->argv[0], data->list->head);
	if (!data->path)
	{
		close_redir_fds();
		exit_child(data, errno, cmds->argv[0], ": command not found");
	}
	execve(data->path, cmds->argv, data->envp);
	close_redir_fds();
	if (errno == EACCES)
		exit_child(data, errno, cmds->argv[0], ": permission denied");
	if (data->cmds->redir && data->cmds->redir->file)
		exit_child(data, errno, cmds->argv[0], "No such file or directory");
	exit_child(data, errno, cmds->argv[0], ": Not a directory");
}

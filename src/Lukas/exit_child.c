/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:02:05 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/08 14:57:35 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"
/*
static void	child_write(char *error, char *msg)
{
	write(2, "bash: ", 7);
	write(2, error, ft_strlen(error));
	write(2, msg, ft_strlen(msg));
}
*/

void	exit_child(t_shell *data, char **envp, char *path, int err, char *msg)
{
	int	exit_code;

	exit_code = err;
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->list)
		free_environment(data->list);
	if (data->fds)
		close_backup_fds(data->fds);
	if (data->input)
		free(data->input);
	if (path)
		free(path);
	if (envp)
		free_arr(envp);
	(void)msg;
//	child_write(strerror(err), msg);
//	printf("%s", msg);	//find a logic to output the right error!
	exit(exit_code);
}

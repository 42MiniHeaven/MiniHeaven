/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:23:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 17:25:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"
/*
int	exec_pipe(char **cmd, char **env) // change to t_cmd
{
	int	status = 0;
	(void)env;
	int	i = -1;
	while (cmd[++i])
		printf("pipe: %s\n", cmd[i]);
	return (status);
}
*/

int	exec_external(t_mh *mh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
//		setup_child_signals();
//		apply_redirections(cmd);
		execve(resolve_path(mh->cmds.argv[0], mh->llist), mh->cmds.argv, llist_to_env(mh->llist));
//		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	return (status); //(extract_exit_status(status));
}

int	exec_single(t_mh *mh) // change to t_cmd
{
	int	status = 0;

//	if (!cmd->argv || !cmd->argv[0])
//		return (apply_redirs_only(cmd));
	if (is_builtin(mh->cmds.argv[0]))
	{
//		if (apply_redirections(cmd) != 0)
//			return (1);
		status = exec_builtin(mh);
//		restore_std_fds();
		return (status);
	}
	else
		return (exec_external(mh));
}

int	dispatcher(t_mh *mh) //change to t_cmd
{
	int	status = 0;

	if (!mh || !mh->cmds.argv[0])
		return (0);
	if (!mh->cmds.next) //change to ->next
//	if	(handle_all_heredocs(cmds) != 0)
//		return (1);
		status = exec_single(mh);
//	else
//		printf("no piping yet!\n");
//		status = exec_pipe(cmds, env);
//	update_exit_status(status);
	return (status);
}

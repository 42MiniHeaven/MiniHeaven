/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:23:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/07 21:47:34 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	exec_pipe(t_cmd *cmds, t_env *env)
{
	return (dispatch_pipeline(cmds, env));
}


int	exec_external(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
//		setup_child_signals();
//		apply_redirections(cmd);
		execve(resolve_path(cmds->argv[0], env), cmds->argv, llist_to_env(env));
//		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	return (status); //(extract_exit_status(status));
}

int	exec_single(t_cmd *cmds, t_env *env) // change to t_cmd
{
	int	status = 0;

//	if (!cmd->argv || !cmd->argv[0])
//		return (apply_redirs_only(cmd));
	if (is_builtin(cmds->argv[0]))
	{
//		if (apply_redirections(cmd) != 0)
//			return (1);
		status = exec_builtin(cmds, env);
//		restore_std_fds();
		return (status);
	}
	else
		return (exec_external(cmds, env));
}

int	dispatcher(t_cmd *cmds, t_env *env) //change to t_cmd
{
	int	status = 0;

	if (!cmds || !cmds->argv[0])
		return (0);
	if (!cmds->next) //change to ->next
//	if	(handle_all_heredocs(cmds) != 0)
//		return (1);
		status = exec_single(cmds, env);
	else
		status = exec_pipe(cmds, env);
//	update_exit_status(status);
	return (status);
}

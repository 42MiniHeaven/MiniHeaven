/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:23:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/12 19:54:34 by lwittwer         ###   ########.fr       */
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
		if (apply_redirections(cmds->redirs))
			return (1);
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
//		return (apply_redirs_only(cmds->redirs));
	if (is_builtin(cmds->argv[0]))
	{
		if (apply_redirections(cmds->redirs) != 0)
		{
			restore_std_fds(cmds->stdfds);
			return (1);
		}
		printf("single\n");
		status = exec_builtin(cmds, env);
		restore_std_fds(cmds->stdfds);
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
	if	(handle_all_heredocs(cmds) != 0)
		return (1);
	if (!cmds->next) //change to ->next
		status = exec_single(cmds, env);
	else
		status = exec_pipe(cmds, env);
//	update_exit_status(status);
	return (status);
}

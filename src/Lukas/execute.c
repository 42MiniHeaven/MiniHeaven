/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:23:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/03 19:59:10 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

int	exec_pipe(char **cmd, char **env) // change to t_cmd
{
	int	status = 0;
	(void)env;
	int	i = -1;
	while (cmd[++i])
		printf("pipe: %s\n", cmd[i]);
	return (status);
}
/*
int	exec_external(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		apply_redirections(cmd);
		execve(resolve_path(cmd->argv[0], *env), cmd->argv, env_to_array(*env));
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	return (extract_exit_status(status));
}
*/

int	exec_single(char **cmd, char **env) // change to t_cmd
{
	int	status = 0;

	(void)env;
	printf("single cmd: %s\n", cmd[0]);
	return (status);
//	if (!cmd->argv || !cmd->argv[0])
//		return (apply_redirs_only(cmd));
//	if (is_builtin(cmd->argv[0]))
//	{
//		if (apply_redirections(cmd) != 0)
//			return (1);
//		status = exec_builtin(cmd, env);
//		restore_std_fds();
//		return (status);
//	}
//	return (exec_external(cmd, env));
}

int	execute(char **cmds, char **env) //change to t_cmd
{
	int	status = 0;

	if (!cmds || cmds != NULL)
	{
		printf("No cmd found.\n");
		return (0);
	}
	(void)env;
//	if	(handle_all_heredocs(cmds) != 0)
//		return (1);
	if (!cmds[1]) //change to ->next
		status = exec_single(cmds, env);
	else
		status = exec_pipe(cmds, env);
//	update_exit_status(status);
	return (status);
}

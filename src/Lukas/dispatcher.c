/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:23:27 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/05 19:19:54 by lwittwer         ###   ########.fr       */
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

int	exec_single(t_cmd *cmd, char **env) // change to t_cmd
{
	int	status = 0;

	(void)env;
	printf("single cmd: %s\n", cmd->argv[0]);
//	if (!cmd->argv || !cmd->argv[0])
//		return (apply_redirs_only(cmd));
	if (is_builtin(cmd->argv[0]))
	{
		printf("it is a builtin\n");
//		if (apply_redirections(cmd) != 0)
//			return (1);
//		status = exec_builtin(cmd, env);
//		restore_std_fds();
//		return (status);
	}
	else
		printf("it is an external\n");
//	return (exec_external(cmd, env));
	return (status);
}

int	dispatcher(t_cmd *cmd, char **env) //change to t_cmd
{
	int	status = 0;

	if (!cmd || !cmd->argv[0])
		return (0);
	(void)env;	//no need right now
//	if	(handle_all_heredocs(cmds) != 0)
//		return (1);
	if (!cmd->next) //change to ->next
		status = exec_single(cmd, env);
//	else
//		printf("no piping yet!\n");
//		status = exec_pipe(cmds, env);
//	update_exit_status(status);
	return (status);
}

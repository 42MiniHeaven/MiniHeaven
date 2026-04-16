/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:52:43 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 20:23:47 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

// General execution
int		execute(t_shell *data);
int		exec_builtin(t_shell *data);
int		exec_external(t_shell *data);
int		exec_pipe(t_shell *data);
int		exec_single(t_shell *data);

// Processes handling
void	child(t_cmd *cmds, t_shell *data);
void	child_error(char *error, char *msg);
void	exit_child(t_shell *data, int exit_code, char *error, char *msg);

// File descriptor handling
int		safe_std_fds(t_shell *data);
void	restore_std_fds(t_fds *saved);
void	close_all_fds(void);
void	close_backup_fds(t_fds *saved);

// Builtins
int		builtin_cd(t_cmd *cmd, t_environment *list);
int		builtin_echo(t_cmd *cmd, t_environment *list);
int		builtin_env(t_cmd *cmd, t_environment *list);
int		builtin_exit(t_cmd *cmd, t_shell *data);
int		builtin_export(t_cmd *cmd, t_environment *list);
int		builtin_pwd(t_cmd *cmd, t_environment *list);
int		builtin_unset(t_cmd *cmd, t_environment *list);

// Redirections
int		setup_redirections(t_redir *redir);
void	close_redir_fds(void);
char	*resolve_path(char *cmd, t_env *env);

// Utils / wrappers
int		is_builtin(const char *name);
int		wopen(const char *path, int flags, mode_t mode);
pid_t	wfork(void);
void	wclose(int fd);
void	wdup2(int oldfd, int newfd);
void	wpipe(int pipefd[2]);

#endif

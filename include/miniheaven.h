/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/25 13:24:57 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

# include <stdio.h>					// printf
# include <unistd.h>				// write
# include <stdlib.h>				// malloc
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// waitpid
# include <fcntl.h>					// open flags
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../Libft/include/libft.h"
# include "../src/AJ/parser.h"
# include "../src/Lukas/env/env.h"
# include "../src/Lukas/builtins/builtins.h"

// Maybe delete later
# include <aio.h>
# include <ctype.h>

typedef struct s_token	t_token;
typedef struct s_shell	t_shell;
typedef struct s_fds	t_fds;

// main structure comtaining everything, which also can be freed easily
struct	s_shell
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		exit_code;
	int		status;
	t_env	*lst;
	t_fds	*fds;
	int		last_signal;
};

struct	s_fds
{
	int	in;
	int	out;
	int	err;
};
//PROTOTYPES GENERAL

//free.c
void	free_arr(char **arr);
void	free_str(char *str);

//free_call.c
void	free_call(t_shell data, int args, char *input);
void	free_tokens(t_token *lst);
void	free_cmds(t_cmd *lst);
void	free_shell(t_shell *data);
void	free_env(t_env *head);

//init.c
void	init_shell(t_shell *data, char **envp);

//PROTOTYPES LUKAS

//dispatcher.c
int		dispatcher(t_cmd *cmds, t_env *lst, t_fds *fds, int *status);

//exec_builtin.c
int		exec_builtin(t_cmd *cmds, t_env *env);

//exec_external.c
int		exec_external(t_cmd *cmds, t_env *env);

//exec_pipe.c
int		exec_pipe(t_cmd *cmds, t_env *env);

//exec_single.c
int		exec_single(t_cmd *cmds, t_env *env, t_fds *fds);

//fds.c
int		safe_std_fds(t_shell *data);
void	restore_std_fds(t_fds *saved);

//heredoc.c
int		handle_heredoc(t_redir *redir);
int		handle_all_heredocs(t_cmd *cmds);

//init_empty_env.c
void	init_empty_env(t_env **lst);

//redirections.c
int		apply_redirections(t_redir *redir);

//resolve_path.c
char	*resolve_path(char *cmd, t_env *env);

//builtins.c
int		is_builtin(const char *name);
#endif

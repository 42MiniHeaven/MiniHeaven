/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/02/14 18:06:59 by lwittwer         ###   ########.fr       */
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

typedef struct	s_shell	t_shell;
typedef struct	s_fds	t_fds;

// main structure comtaining everything, which also can be freed easily
struct	s_shell
{
	t_token *tokens;
	t_cmd	*cmds;
	int		exit_code;
	t_env	*llist;
	t_fds	*fds;
	int		last_signal;
};

struct	s_fds
{
	int	in;
	int	out;
	int	err;
};

//PROTOTYPES LUKAS
//init.c
void	init_shell(t_shell *data, char **envp);

//dispatcher.c
int		dispatcher(t_cmd *cmds, t_env *env, t_fds *fds);

//builtins.c
builtin_func	find_builtin(const char *name);
int				is_builtin(const char *name);

//free.c
void	free_arr(char **arr);
void	free_str(char *str);
void	free_linked(t_env *head);

//exec_builtin.c
int		exec_builtin(t_cmd *cmds, t_env *env);

//resolve.c
char	*resolve_path(char *cmd, t_env *env);

//forking.c
int		dispatch_pipeline(t_cmd *cmds, t_env *env);

//redirections.c
int		apply_redirections(t_redir *redit);

//fds.c
int		safe_std_fds(t_shell *data);
void	restore_std_fds(t_fds *saved);

//heredoc.c
int	handle_heredoc(t_redir *redir);
int	handle_all_heredocs(t_cmd *cmds);

#endif

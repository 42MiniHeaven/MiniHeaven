/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/03/27 19:57:57 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEAVEN_H
# define MINIHEAVEN_H

// needed for sigaction()
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include <stdio.h>					// printf
# include <unistd.h>				// write
# include <stdlib.h>				// malloc
# include <stdbool.h>				// boolean data type (bool)
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// waitpid
# include <fcntl.h>					// open flags
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/include/libft.h"
# include "../src/AJ/parser.h"
# include "../src/Lukas/env/env.h"
# include "../src/Lukas/builtins/builtins.h"

// Maybe delete later
# include <aio.h>
# include <ctype.h>

typedef struct s_token	t_token;
typedef struct s_shell	t_shell;
typedef struct s_fds	t_fds;
typedef struct s_parser	t_parser;

// main structure comtaining everything, which also can be freed easily
struct	s_shell
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_environment	*list;
	t_fds			*fds;
	int				last_exit;
	int				should_exit;
};

struct	s_parser
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tok;
	int		state;
	int		last_redir;
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

//free_environment.c
void	free_environment(t_environment *list);

//free_fds.c
//void	free_fds(t_shell *data);

//free_call.c
void	free_call(t_shell data, int args, char *input);
void	free_tokens(t_token *lst);
void	free_cmds(t_cmd *lst);
void	free_shell(t_shell *data);
void	free_env(t_env *head);

//shell_init.c
void	shell_init(t_shell *data, char **envp);

//error.c
void	ft_error(char *func, char *error, int fd);

//check_args.c
void	check_args(int argc, char **argv, char **envp);

//loop.c
void	loop(t_shell *data);

//loop_utils.c
void	reset_shell(t_shell *data);
void	free_loop(t_shell *data);

//fake_cmd.c
void	fake_cmd(t_cmd **cmd);

//on_failure.c
//void	on_failure(t_shell *data, char *issue);

//PROTOTYPES AJ

//parser_utils.c
t_cmd	*cmd_new(void);
int		cmd_add_arg(t_cmd *cmd, const char *word);
t_redir	*redir_new(int type, const char *file);
char	**argv_realloc(char **old, int old_len, int new_len);

//parser_utils2.c
int		cmd_add_redir(t_cmd *cmd, int type, const char *filename);
int		cmd_add_back(t_cmd **head, t_cmd *new);

//PROTOTYPES LUKAS

//child.c
void	child(t_cmd *cmds, t_environment *list);

//child_utils.c
void	child_error(char *error, char *msg);

//execute.c
int		execute(t_shell *data);

//exec_builtin.c
int		exec_builtin(t_shell *data);

//exec_external.c
int		exec_external(t_shell *data);

//exec_pipe.c
int		exec_pipe(t_shell *data);

//exec_single.c
int		exec_single(t_shell *data);

//fds.c
int		safe_std_fds(t_shell *data);
void	restore_std_fds(t_fds *saved);

//heredoc.c
int		handle_heredoc(t_redir *redir);
int		handle_all_heredocs(t_cmd *cmds);

//empty_env_lst_init.c
void	empty_env_init(t_shell *data);

//redirections.c
int		setup_redirections(t_redir *redir);

//resolve_path.c
char	*resolve_path(char *cmd, t_env *env);

//builtins.c
int		is_builtin(const char *name);

//env_arr.c
char	**env_arr(t_env *env);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheaven.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:23:25 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 14:23:33 by lwittwer         ###   ########.fr       */
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
# include <sys/ioctl.h>				// needed for signals
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/include/libft.h"
# include "parser.h"
# include "env.h"
# include "builtins.h"

# define TMP_DIR "/tmp"
# define MAX_ATTEMPTS 1000
# define HEREDOC_MAX_SIZE (1024 * 1024)

typedef struct s_token	t_token;
typedef struct s_shell	t_shell;
typedef struct s_fds	t_fds;
typedef struct s_parser	t_parser;
typedef struct s_hdnode	t_hdnode;

// main structure comtaining everything, which also can be freed easily
struct	s_shell
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_environment	*list;
	t_fds			*fds;
	int				last_exit;
	int				should_exit;
	char			*input;
	char			**envp;
	char			*path;
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

struct	s_hdnode
{
	t_redir			*redir;
	struct s_hdnode	*next;
};

//PROTOTYPES GENERAL

//free.c
void	free_arr(char **arr);

//free_environment.c
void	free_environment(t_environment *list);

//free_fds.c
//void	free_fds(t_shell *data);

//free_call.c
void	free_tokens(t_token *lst);
void	free_cmds(t_cmd *lst);
void	free_fds(t_fds *fd);

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


//PROTOTYPES AJ

//parser_utils.c
t_cmd	*cmd_new(void);
bool	cmd_add_arg(t_cmd *cmd, const char *word);
t_redir	*redir_new(int type, const char *file);
char	**argv_realloc(char **old, int old_len, int new_len);

//parser_utils2.c
bool	cmd_add_redir(t_cmd *cmd, int type, const char *filename);
bool	cmd_add_back(t_cmd **head, t_cmd *new);

//2_parser_cleanup.c
void	parser_exit(t_parser *p);

//expander_utils.c
char	**expander_split(char *s, char *delim);

//4_heredoc.c
int		prepare_heredocs(t_shell *data, t_cmd *cmds);

//4_expander_heredoc.c 
char	*expand_line(t_shell *data, char *input);

//PROTOTYPES LUKAS

//child.c
void	child(t_cmd *cmds, t_shell *data);

//child_utils.c
void	child_error(char *error, char *msg);

//exit_child.c
void	exit_child(t_shell *data, int exit_code, char *error, char *msg);

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
void	close_all_fds(void);
void	close_backup_fds(t_fds *saved);

//heredoc.c
int		create_heredoc(t_redir *hd, t_shell *data);

//heredoc_utils.c
int		is_delimiter(char *line, char *eof);
char	*process_line(t_redir *hd, t_shell *data, char *line);
char	*read_heredoc_line(void);

//heredoc_tmpfile.c
int		create_heredoc_tmpfile(char *path_out, char *eof);

//empty_env_lst_init.c
void	empty_env_init(t_shell *data);

//redirections.c
int		setup_redirections(t_redir *redir);
void	close_redir_fds(void);

//resolve_path.c
char	*resolve_path(char *cmd, t_env *env);

//builtins.c
int		is_builtin(const char *name);

//env_arr.c
char	**env_arr(t_env *env);

//wrapper.c

//wopen.c
int		wopen(const char *path, int flags, mode_t mode);

//wclose.c
void	wclose(int fd);

//wdup2.c
void	wdup2(int oldfd, int newfd);

//wfork.c
pid_t	wfork(void);

//wpipe.c
int		wpipe(int pipefd[2]);

//fatal.c
void	fatal(const char *msg, int exit_code);


// TESTING PURPOSES
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
char	*get_next_line(int fd);
char	*read_file(int fd);

#endif

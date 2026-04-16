/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:05:25 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 20:23:23 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniheaven.h"

// Main structs
typedef struct s_shell			t_shell;
typedef struct s_token			t_token;
typedef struct s_redir			t_redir;
typedef struct s_cmd			t_cmd;

// Helper structs
typedef struct s_parser			t_parser;
typedef struct s_fds			t_fds;
typedef struct s_hdnode			t_hdnode;
typedef struct s_env			t_env;
typedef struct s_environment	t_environment;

enum	e_token_type
{
	WORD = 0,
	PIPE = 1,
	REDIR_OUT = 2,
	REDIR_IN = 3,
	APPEND = 4,
	HEREDOC = 5
};

enum	e_parser_state
{
	EXPECT_COMMAND = 0,
	EXPECT_ARG_OR_REDIR = 1,
	EXPECT_REDIR_TARGET = 2
};

/* 	
	WORD		ls, -l, filename
	PIPE		|
	REDIR_OUT	>
	REDIR_IN	<
	APPEND		>>
	HEREDOC		<<
*/

// Main structure comtaining everything
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

// Product of the lexer
struct	s_token
{
	char	*value;
	int		type;
	t_token	*next;
};

// Product of the parser
struct	s_cmd
{
	// char	*cmd;	// command only
	char	**argv;	// flags ["-l", NULL], dymanic uses realloc
	t_redir	*redir;	// linked list of redirections
	t_cmd	*next;	// next command in pipeline
};

// Redirection node, expansion for the parser product
struct	s_redir
{
	int		type;	// REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	int		expand;
	char	*file;
	char	*tmp_file;
	bool	success;
	t_redir	*next;
};

// Helper struct for the functions in the parser section
struct	s_parser
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tok;
	int		state;
	int		last_redir;
};

// Helper struct containing the backup of the file descriptors
struct	s_fds
{
	int	in;
	int	out;
	int	err;
};

// Helper struct for heredocs
struct	s_hdnode
{
	t_redir			*redir;
	struct s_hdnode	*next;
};

struct	s_env
{
	int				flag;
	char			*key;
	char			*value;
	struct s_env	*next;
};

struct	s_environment
{
	t_env	*head;
	int		size;
};

#endif
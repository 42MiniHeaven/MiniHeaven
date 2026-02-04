/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/04 22:23:28 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../Libft/include/libft.h"

typedef struct	s_token t_token;
typedef struct  s_redir t_redir;
typedef struct  s_cmd t_cmd;

/* 	
	WORD		ls, -l, filename
	PIPE		|
	REDIR_OUT	>
	REDIR_IN	<
	APPEND		>>
	HEREDOC		<<
*/

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

// Product of the lexer
struct s_token
{
	char            *value;
	int             type;
	struct s_token  *next;
};

// Redirection node, expansion for the parser product
struct  s_redir
{
	int             type;   // REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char            *file;
	struct s_redir  *next;
};

// Product of the parser
struct s_cmd 
{
	char        *cmd;	// command only
	char		**argv;	// flags ["-l", NULL], dymanic uses realloc
	t_redir		*redir; // linked list of redirections
	t_cmd       *next;  // next command in pipeline
};

t_token *lexer(char *input);
t_cmd   *parse(t_token *tokens);
void	destroy_all(t_cmd *cmds, t_token *tokens);

#endif

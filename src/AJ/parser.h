/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/19 20:01:09 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct	s_token t_token;
typedef struct  s_redir t_redir;
typedef struct  s_cmd t_cmd;

enum e_token_type
{
	WORD = 0,       	// ls, -l, filename
	PIPE = 1,       	// |
	REDIR_OUT = 2,  	// >
	REDIR_IN = 3,   	// <
	APPEND = 4,     	// >>
	HEREDOC = 5     	// <<
};

// Product of the lexer
struct s_token
{
	char            *value;
	int             type;
	struct s_token  *next;
};

// Product of the parser
struct s_cmd 
{
	char		*cmd;   // command itself; ["ls"]
	char        **argv; // command flag or not ["-l", NULL]
	t_redir		redir; // linked list of redirections
	t_cmd       *next;  // next command in pipeline
};

// Redirection node, expansion for the parser product
struct  s_redir
{
	int             type;   // REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char            *file;
	struct s_redir  *next;
};

#endif

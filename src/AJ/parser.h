/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/09 17:15:56 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "../../include/miniheaven.h"

typedef struct s_shell t_shell;
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
	int				fd;
	int				expand;
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

// SIGNALHANDLING
void	handle_signals_prompt(void);
void	handle_signals_exec_parent(void);
void	handle_signals_exec_child(void);
void	set_exit_code(t_shell *data);
// int		rl_hook(void);

// TOKENISING & LEXING
void	tokeniser(t_shell *data, char *input);
void	create_token(char *input, int *i, int start, t_token **tokens);
void	token_add_back(t_token **list, t_token *new);
t_token	*token_new(int type, char *value);
bool	lex_unclosed_quotes(char *input, int *i);

// PARSING
int		parser(t_shell *data);
int		syntax_error(char *message);

// EXPANSION
bool	resolve_quotes(char **argv);
bool	needs_expansion_word(char *word, char *mask);
bool	needs_expansion_argv(char **arr);
bool	need_heredoc_expansion(char *str);
bool	needs_wordsplitting(char *str);
char	*create_mask(char *str);
char	*join_argv(char **argv);
char	*handle_env_var(char *word, int *i, char *result, t_shell *data);
char	*str_join_free(char *str1, char *str2);
char	*append_char(char *str, char c);
char	*replace_var(t_shell *data, char *word, char *mask);
char	*handle_dollar(t_shell *d, char *w, int *i, char *res, char *exit);
char	*handle_heredoc_quotes(char *str);
char	**argv_replace_word_with_split(char **argv, int idx, char **split);
int		argv_len(char **argv);


// COULD BE ADDED TO LIBFT
int 	ft_is_operator(int c);
int		ft_isspace(int c);
char	**ft_realloc(char **old, size_t old_count, size_t new_count);


// void	destroy_all(t_cmd *cmds, t_token *tokens);

// void	check_signals(t_shell data);
void	expand_commands(t_shell *data);

#endif

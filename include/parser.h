/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 18:34:40 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/miniheaven.h"

# include "structs.h"



// SIGNALHANDLING
void	handle_signals_prompt(void);
void	handle_signals_exec_parent(void);
void	handle_signals_exec_child(void);
void	set_exit_code(t_shell *data);
void    handle_signals_heredoc(void);
void	handle_sig(int sigtype);
int		rl_hook(void);
int		rl_heredoc_hook(void);


// int		rl_hook(void);

// TOKENISING & LEXING
void	tokeniser(t_shell *data, char *input);
void	create_token(char *input, int *i, int start, t_token **tokens);
void	token_add_back(t_token **list, t_token *new);
t_token	*token_new(int type, char *value);
bool	lex_unclosed_quotes(char *input, int *i);

// PARSING
void	parser_init(t_parser *p, t_shell *data);
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
char	*handle_dollar(t_shell *d, char *w, int *i, char *res);
char	*handle_heredoc_quotes(char *str);
char	**argv_replace_word_with_split(char **argv, int idx, char **split);
int		argv_len(char **argv);
bool	expand_redir(t_cmd *cmd, t_shell *data);
bool	in_str(char c, char *str);

// REDIRECTIONS
char	*replace_file_var(t_shell *data, t_redir *tmp, char *mask);
void	redir_error(t_redir *tmp);

// GENERAL UTILS
int		count_len(char *mask);
char	*remove_quotes(char *word, char *mask);


// COULD BE ADDED TO LIBFT
int 	ft_is_operator(int c);
int		ft_isspace(int c);
char	**ft_realloc(char **old, size_t old_count, size_t new_count);


// void	destroy_all(t_cmd *cmds, t_token *tokens);

// void	check_signals(t_shell data);for the functions in the parser section
void	expand_commands(t_shell *data);

#endif

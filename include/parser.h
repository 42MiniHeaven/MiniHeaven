/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 22:16:42 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

// SIGNAL HANDLING
int		rl_heredoc_hook(void);
int		rl_hook(void);
void	handle_signals_prompt(void);
void	handle_signals_exec_parent(void);
void	handle_signals_exec_child(void);
void	set_exit_code(t_shell *data);
void	handle_signals_heredoc(void);
void	handle_sig(int sigtype);

// TOKENISING & LEXING
t_token	*token_new(int type, char *value);
void	tokeniser(t_shell *data, char *input);
void	create_token(char *input, int *i, int start, t_token **tokens);
void	token_add_back(t_token **list, t_token *new);
bool	lex_unclosed_quotes(char *input, int *i);

// PARSING
t_cmd	*cmd_new(void);
t_redir	*redir_new(int type, const char *file);
void	parser_init(t_parser *p, t_shell *data);
int		parser(t_shell *data);
int		syntax_error(char *message);
char	**argv_realloc(char **old, int old_len, int new_len);
bool	cmd_add_arg(t_cmd *cmd, const char *word);
bool	cmd_add_redir(t_cmd *cmd, int type, const char *filename);
bool	cmd_add_back(t_cmd **head, t_cmd *new);
void	parser_exit(t_parser *p);

// General utils
int		count_len(char *mask);
int		ft_is_operator(int c);
int		ft_isspace(int c);
char	*remove_quotes(char *word, char *mask);
char	**ft_realloc(char **old, size_t old_count, size_t new_count);

#endif

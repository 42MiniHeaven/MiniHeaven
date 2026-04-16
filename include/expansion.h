/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:43:01 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 20:25:13 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"

// Limits the heredoc size not to fill up the file
# define TMP_DIR "/tmp"
# define MAX_ATTEMPTS 1000
# define HEREDOC_MAX_SIZE 1048576	// Thats a megabyte

// General
void	expand_commands(t_shell *data);
char	*expand_line(t_shell *data, char *input);
bool	expand_redir(t_cmd *cmd, t_shell *data);

// Variable expansion logic
char	*handle_env_var(char *word, int *i, char *result, t_shell *data);
char	*handle_dollar(t_shell *d, char *w, int *i, char *res);
char	*replace_var(t_shell *data, char *word, char *mask);
char	*replace_file_var(t_shell *data, t_redir *tmp, char *mask);

// Expander split
char	**expander_split(char *s, char *delim);
char	**argv_replace_word_with_split(char **argv, int idx, char **split);
bool	needs_wordsplitting(char *str);

// Quote handling
bool	resolve_quotes(char **argv);
bool	need_heredoc_expansion(char *str);
char	*create_mask(char *str);
char	*handle_heredoc_quotes(char *str);

// Expander check
bool	needs_expansion_word(char *word, char *mask);
bool	needs_expansion_argv(char **arr);

// Heredoc
int		prepare_heredocs(t_shell *data, t_cmd *cmds);
int		create_heredoc(t_redir *hd, t_shell *data);
int		create_heredoc_tmpfile(char *path_out, char *eof);
int		is_delimiter(char *line, char *eof);
char	*process_line(t_redir *hd, t_shell *data, char *line);
char	*read_heredoc_line(void);

// Utils
bool	in_str(char c, char *str);
int		argv_len(char **argv);
char	*append_char(char *str, char c);
char	*join_argv(char **argv);
char	*str_join_free(char *str1, char *str2);

#endif
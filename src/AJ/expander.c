/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/14 23:23:18 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

// Before the head is returned to the main including the commands for the execution
// expansion needs to happen.

// Checks for $, handles quotes and removes quotes and replaces it with the expansion.
// 1. Single quotes: Trims quotes only
// 2. Double quotes: Trims quotes and expands varaiable
// 3. No quotes: Expands and splits words
// SPECIAL CASE: HEREDOC
// At some point in the expander it needs to be checked with redirections there are. 
// For heredoc:
// $hi -> does not expand
// "$hi" -> trims quotes only, $ stays
// '$hi' -> trims quotes only, $ stays

// Possible architechture:
// expand_commands()
//    expand_cmd()
//       expand_word()
//          handle_quotes()
//          expand_variables()
//          remove_quotes()

// struct	s_shell
// {
// 	t_token *tokens;
// 	t_cmd	*cmds;
// 	int		exit_code;
// 	int		last_signal;
// 	t_env	*llist;
// 	t_fds	*fds;
// }

// struct s_cmd 
// {
// 	char        *cmd;	// command only
// 	char		**argv;	// flags ["-l", NULL], dymanic uses realloc
// 	t_redir		*redir; // linked list of redirections
// 	t_cmd       *next;  // next command in pipeline
// }

// ------------------------------------------------------------------------

void	fill_mask(char *str, char *mask, int *i, char c, char type)
{
	mask[(*i)++] = 'Q';
	while (str[*i] && str[*i] != c)
		mask[(*i)++] = type;
	if (str[*i])
		mask[(*i)++] = 'Q';
}

static char	*create_mask(char *str)
{
	int	i;
	char	*mask;

	mask = calloc((strlen(str) + 1), sizeof(char));
	if (!mask)
		return NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			fill_mask(str, mask, &i, '"', 'D');
		else if (str[i] == '\'')
			fill_mask(str, mask, &i, '\'', 'S');
		else
			mask[i++] = 'N';
	}
	return (mask);	
}

int	needs_expansion(char *word) // make it a bool?
{
	return (ft_strchr(word, '$'));
}

// Checks for $, handles quotes and removes quotes and replaces it with the expansion.
// 1. Single quotes: Trims quotes only
// 2. Double quotes: Trims quotes and expands varaiable
// 3. No quotes: Expands and splits words

char	*expand_variables(char *word, char *mask, t_shell *data)
{
	if (needs_expansion(word))
	{
		
	}
	return (word);
	
}

char *expand_word(char *word, t_shell *data)
{
	char *mask;

	mask = create_mask(word);
	word = expand_variables(word, mask, data); // needs to be created
	word = remove_quotes(word); // needs to be created	
	
	// also word splitting if needed
	
	free(mask);
	return (word);
}

/*
 * DESCRIPTION
 * Calls expanders for all command nodes (command string, argument list(argv)
 * and redirection targets).
 */

void	expand_cmd(t_cmd *cmd, t_shell *data)
{
	if (cmd->cmd)
		cmd->cmd = expand_word(cmd->cmd, data);
	if (cmd->argv)
		expand_agrs(cmd->argv, data); // needs to be created
	if (cmd->redir)
		expand_redir(cmd->redir, data); // needs to be created
}

/*
 * DESCRIPTION
 * Iterates throuh the command list stored in the t_shell struct and performs
 * expansion on each command node. Calls expand_cmd() for every command in
 * the pipeline.
 *  ?????Protects heredoc delimiters from expanding.
 *
 * VARAIABLES
 * t_cmd *tmp_cmd is a temporary pointer which is used not to destroy the 
 * head pointer of data->cmds itself.
 */

 // How should redirections be handles here??? Should there genereally be
 // be a special case for redirections??

void	expand_commands(t_shell *data)
{
	t_cmd	*tmp_cmd;
	
	tmp_cmd = data->cmds;
	while (tmp_cmd)
	{
		expand_cmd(tmp_cmd, &data);
		tmp_cmd = tmp_cmd->next;
	}
}
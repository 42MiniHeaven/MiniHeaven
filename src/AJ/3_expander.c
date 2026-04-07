/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/07 23:18:43 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * *** EXPANDER ***
 * The expander replaces variables and handles quotes in tokens.
 * 
 * - Single quotes: remove quotes, no expansion
 * - Double quotes: remove quotes, expand variables
 * - No quotes: expand variables, word splitting if needed
 * 
 * Special case: HEREDOC
 * In heredoc, no variable expansion occurs. Quotes are trimmed but any '$'
 * characters remain unchanged.
 */

char	*expand_variables(char *word, char *mask, t_shell *data)
{
	char	*expanded_word;
	
	if (!needs_expansion_word(word, mask))
		return (word);
	expanded_word = replace_var(data, word, mask);
	free(word);
	return (expanded_word);
}

char *expand_word(char *word, t_shell *data)
{
	char *mask;

	mask = create_mask(word);
	word = expand_variables(word, mask, data);
	free(mask);
	return (word);
}

/*
 * DESCRIPTION
 * Expands all arguments of a command node.
 * 
 * Iterates through cmd->argv and applies expansion to each argument using
 * expand_word().
 * 
 * PARAMETERS
 * @param	Pointer to command structure to process.
 * @param	Pointer to shell structure containing environment data.
 * 
 * BEHAVIOUR
 * @note	Modifies cmd->argv in place.
 */

 // How should redirections be handles here??? Should there genereally be
 // be a special case for redirections??

 // For heredoc:
// $hi -> does not expand
// "$hi" -> trims quotes only, $ stays
// '$hi' -> trims quotes only, $ stays

void	expand_cmd(t_cmd *cmd, t_shell *data)
{
	int		i;
	char	**tmp;
	int		error;

	i = 0;
	while (cmd->argv[i])
	{
		cmd->argv[i] = expand_word(cmd->argv[i], data);
		i++;
	}
	error = 1;
	if (needs_wordsplitting(cmd->argv[i], &error))
	{
		tmp = expander_split(join_argv(cmd->argv), " \t\n");
		free_arr(cmd->argv);
		cmd->argv = tmp;
		i++;
	}
	if (error = -1)
		printf("Something needs to be done, Lukas\n"); //TODO: Lukas take care please <3 calloc failed
	if (!resolve_quotes(cmd->argv))
		printf("failed on quotes removal\n");
	// if (cmd->redir)
	// 	expand_redir(cmd->redir, data); // needs to be created
}

/*
 * DESCRIPTION 
 * Iterates through command list data->cmds and performs an expansion on each 
 * command node. Calls expand_cmd() for every command in the pipeline, then
 * joins and splits arguments to handle word splitting (only for not quoted
 * expansion) and removes quotes if no futher expansion is needed.
 * 
 * PARAMETERS
 * @param data:		Pointer to the shell structure containing the pointer
 * 					to the command struct.
 * @param tmp_cmd:	A temporary pointer which is used not to destroy the head 
 * 					pointer of data->cmds itself.
 * 
 * BEHAVIOUR
 * @note	Modifies cmd->argv for each command node.
 * @note	Allocates and frees memory during join/split operations.
 * @note	Advances through command list using a temporary pointer.
 */

void	expand_commands(t_shell *data)
{
	t_cmd	*tmp_cmd;
	
	tmp_cmd = data->cmds;
	while (tmp_cmd)
	{
		expand_cmd(tmp_cmd, data);
		tmp_cmd = tmp_cmd->next;
	}
}


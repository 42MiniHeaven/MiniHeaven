/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:43:39 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/10 16:31:20 by azielnic         ###   ########.fr       */
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

char	*expand_word(char *word, t_shell *data)
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
	char	**tmp;
	int		i;
	int		split_len;

	i = 0;
    while (cmd->argv[i])
    {
        cmd->argv[i] = expand_word(cmd->argv[i], data);
        if (needs_wordsplitting(cmd->argv[i]))
        {
            tmp = expander_split(cmd->argv[i], " \t\n");
            if (!tmp)
                return ;
            split_len = argv_len(tmp);
            cmd->argv = argv_replace_word_with_split(cmd->argv, i, tmp);
            i += split_len;
            continue ;
        }
        i++;
    }
	if (!resolve_quotes(cmd->argv))
		printf("failed on quotes removal\n");
	if (cmd->redir)
	{
		if (!expand_redir(cmd, data))
			printf("failed on redir expansion\n");
	}
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


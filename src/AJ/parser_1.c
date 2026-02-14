/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/18 21:34:58 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Why return type t_cmd* ? 
// --> Parser is creating the list, not modifying an existing one.
// Why t_token *tokens and not t_token **tokens?
// --> The pipeline is the top level, so parse_pipeline consumes all tokens.
// t_cmd   *parse_pipeline(t_token *tokens)
// {
//     t_cmd *cmds;
//     cmds = NULL;
//     while (tokens) // could lead to issues think of including length or next 
//     node
//     {
//         cmds = parse_cmommand(&tokens);
//     }
//     return;
// }
int	check_operators(t_token *tokens, t_token *current, t_token *prev)
{
    // example: echo > file.txt
    // example: echo hello | > file.txt
	while (current != NULL)
    {
		if ((current->type > 0 && current->type < 6) && prev 
			&& (prev->type > 1 && prev->type < 6))
		{
			ft_putstr_fd("Syntax error: two consecutive redirectors", 2);
			return (0); // free gedöns
		}
		prev = current;
		current = current->next;
	}
}

int	check_redirections(t_token *tokens, t_token *current, t_token *prev)
{
    // if (!tokens)
    //     return (1); // empty input ok for redirections - needed?
	if (current->type == APPEND || current->type == REDIR_OUT)
	{
		ft_putstr_fd("Syntax error: >> or > at the beginning", 2);
		return (0); // free gedöns
	}
}

int	check_pipes(t_token *tokens, t_token *current, t_token *prev)
{
    // if (!tokens)
    //     return (1); // empty input ok for pipes - needed?
	if (tokens->type == PIPE)
	{
		ft_putstr_fd("Syntax error: pipe at the beginning\n", 2);
		return (0); // free gedöns
	}
	while (current != NULL) // in case this creates issues create a new varaible
	{
		if (current->type == PIPE && prev && prev->type == PIPE) // to be removed if bonus
		{
			ft_putstr_fd("Syntax error: two consecutive pipes, did not handle bonus\n", 2);
			return (0); // free gedöns
		}
		prev = current;
		current = current->next;
	}
	if (prev && prev->type != WORD)
	{
		printf("Syntax error: word needed at the end\n");
		return (0); // free gedöns
	}
	return (1);
}

int	parse_input_check(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (0);
	current = tokens;
	prev = NULL;
	if (!check_pipes(tokens, current, prev))
		return (0);
	if (!check_redirections(tokens, current, prev))
		return (0);
	if (!check_operators(tokens, current, prev))
		return (0);
	return (1);
}

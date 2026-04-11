/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:29:55 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * *** TOKENISER ***
 * The tokensiser breaks a raw input string into small pieces called tokens.
 *
 * *** LEXER ***
 * The lexer classifies the tokens into types (words and operators) so it is
 * easier to parse.
 */

/*
 * DESCRIPTION
 * Extracts a word token from the input and appends it to the token list.
 * Reads characters until an operator or whitespace is found, checking for
 * unclosed quotes in 'lex_unclosed_quotes()'. The extracted substring is
 * turned into a token by 'create_token()'.
 *
 * PARAMETERS
 * @param tokens:	Token list to append to
 */

static void	lex_word(char *input, int *i, t_token **tokens)
{
	int	start;

	start = *i;
	while (input[*i] && !(ft_is_operator(input[*i]))
		&& !(ft_isspace(input[*i])))
	{
		if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
		{
			if (!lex_unclosed_quotes(input, i))
				return ;
		}
		else
			(*i)++;
	}
	create_token(input, i, start, tokens);
}

/*
 * DESCRIPTION
 * Creates and appends an operator token from input. Uses 'ft_strdup()' to
 * allocate a copy of the operator string so the token owns its memory
 * safely.
 *
 * PARAMETERS
 * @param token:	*token: single newly created token representing the
 * 					current operator
 * @param tokens:	**tokens: the linked list of all tokens produced so far;
 * 					the new token is appended to this list
 */

static void	lex_operator(char *input, int *i, t_token **tokens)
{
	t_token	*token;

	token = NULL;
	if (input[*i] == '|')
		token = token_new(PIPE, ft_strdup("|"));
	else if (input[*i] == '>' && input[(*i) + 1] != '>')
		token = token_new(REDIR_OUT, ft_strdup(">"));
	else if (input[*i] == '<' && input[(*i) + 1] != '<')
		token = token_new(REDIR_IN, ft_strdup("<"));
	else if (input[*i] == '>' && input[(*i) + 1] == '>')
	{
		token = token_new(APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else if (input[*i] == '<' && input[(*i) + 1] == '<')
	{
		token = token_new(HEREDOC, ft_strdup("<<"));
		(*i)++;
	}
	(*i)++;
	token_add_back(tokens, token);
}

/*
 * DESCRIPTION
 * Converts the received input into  a linked list of tokens and prepares
 * them for parsing.
 *
 * Iterates through input string skipping whitespaces. Operators are handled
 * by 'lex_operator()' while word (commands/arguments) are handled by
 * 'lex_word()'.
 *
 * PARAMETERS
 * @param data:		Pointer to the shell structure where the resulting token
 * 					list will be stored (data->tokens).
 * @param input:	Null-terminated string representing the user input.
 *
 * BEHAVIOUR
 * @note:		Does nothing if data or input is NULL.
 * @note:		Modifies the index 'i' through helper functions.
 * @note		Allocates memory for tokens via lex_* functions.
 */

void	tokeniser(t_shell *data, char *input)
{
	t_token	*tokens;
	size_t	input_len;
	int		i;

	tokens = NULL;
	if (!data || !input)
		return ;
	input_len = ft_strlen(input);
	i = 0;
	while ((size_t)i < input_len)
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_is_operator(input[i]))
			lex_operator(input, &i, &tokens);
		else
			lex_word(input, &i, &tokens);
	}
	data->tokens = tokens;
}

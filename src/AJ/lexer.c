/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/27 18:06:45 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/* 
 * LEXER
 * The lexer transforms a raw input string into a linked list of tokens 
 * (words and operators) that are easier to parse. --> Only tokenises
 
 * PARSER
 * Grammar: 
 *              input        → pipeline
 *              pipeline     → command ( '|' command )*
 *              command      → prefix* WORD suffix*
 *              prefix       → redirection
 *              suffix       → WORD | redirection
 *              redirection  → ('>' | '<' | '>>' | '<<') WORD
 * 
 * ????? --> Only interprets structure 
 */

int ft_is_operator(int c)
{
    return (c == '|' || c == '<' || c == '>');
}

// https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/ 
// "A token that contains no quotes and at least one meta-character is an ‘operator’."

// https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/ 
// "A token that contains no quotes and at least one meta-character is an ‘operator’."

int ft_isspace(int c)
{
    return (c == ' ');   // could include more whitespaces (tab and newline)
    // could also include additional separation characters like & , and ;
    return (c == ' ');   // could include more whitespaces (tab and newline)
    // could also include additional separation characters like & , and ;
}

/*
 * DESCRIPTION
 * Adds a new token to the end of the current token list. Function name says what the 
 * functions does (add) and where it does it (back) applying it to tokens.
 * DESCRIPTION
 * Adds a new token to the end of the current token list. Function name says what the 
 * functions does (add) and where it does it (back) applying it to tokens.
 * 
 * NOTE
 * t_token **list is a pointer to the head pointer of the list.
 * In case the list is empty it is needed so the head can be updated.
 * t_token *new is the token to be added.
 * NOTE
 * t_token **list is a pointer to the head pointer of the list.
 * In case the list is empty it is needed so the head can be updated.
 * t_token *new is the token to be added.
 */

void	token_add_back(t_token **list, t_token *new)
{
    t_token	*tmp; // basically our i to find the last node of the list

    if (!list || !new)
        return ;
    if (!*list) // checks is list is empty hence is the head of the list (first entry)
    {
        *list = new;
        return ;
    }
    tmp = *list;
    while (tmp->next) { // goes through list until it finds last node
        tmp = tmp->next;
    }
    tmp->next = new; // new token is liked to last node
}

/*
 * DESCRIPTION
 * Combines the gathered info and ONLY creates a new node.
 * DESCRIPTION
 * Combines the gathered info and ONLY creates a new node.
 */

t_token	*token_new(int type, char *value)
{
    t_token	*token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

void	create_token(char *input, int *i, int start, t_token **tokens)
{
	char	*value;
    t_token	*token;

	value = ft_substr(input, start, *i - start);
    if (!value)
        syntax_error("failure assigning 'value' in lex_word function"); // Free when error;
    token = token_new(WORD, value);
    if (!token)
        syntax_error("failure assigning 'token' in lex_word function"); // Free when error;
    token_add_back(tokens, token);
}

void	lex_word(char *input, int *i, t_token **tokens)
{
 	int	start;

		start = *i;
    while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
	{
        if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
        {
			if (!lex_quotes(input, i))
				return ;
        }
		else
			(*i)++;
	}
	create_token(input, i, start, tokens);
}

/*
 * GENERAL: Determines the operator at input[i], creates the correct token, 
 * appends it and increments i.
 * 
 * NOTE 1:  Usually i is incremented in each function individually. Here i is
 *          inherited from the previous function and can be used there once this
 *          function is done.
 * 
 * NOTE 2:  *token: single newly created token representing the current operator
 *          **tokens: the linked list of all tokens produced so far; the new token
 *          is appended to this list
 */

 // Also explain why str_dup is used

void	lex_operator(char *input, int *i, t_token **tokens)
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
 * Converts the received input into tokens and prepares them for parsing.
 * DESCRIPTION 
 * Converts the received input into tokens and prepares them for parsing.
 * 
 * NOTE
 * Helper functions were created to make the code more readble.
 * NOTE
 * Helper functions were created to make the code more readble.
 */

void	lexer(t_shell *data, char *input)   // should be called tokeniser??
{
	t_token	*tokens;
    size_t	input_len;
    int		i;

//  if (validity_check(input) == 0 / 1);
//      return (error);
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

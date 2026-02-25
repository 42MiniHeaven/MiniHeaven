/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/25 23:24:26 by azielnic         ###   ########.fr       */
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

int ft_isspace(int c)
{
    return (c == ' ');   // could include more whitespaces
}

/*
 * DESCRIPTION
 * Adds a new token to the end of the current token list. Function name says what the 
 * functions does (add) and where it does it (back) applying it to tokens.
 * 
 * NOTE
 * t_token **list is a pointer to the head pointer of the list.
 * In case the list is empty it is needed so the head can be updated.
 * t_token *new is the token to be added.
 */

void    token_add_back(t_token **list, t_token *new)
{
    t_token *tmp; // basically our i to find the last node of the list

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
 */

t_token *token_new(int type, char *value)
{
    t_token *token;

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
	char    *value;
    t_token *token;

	value = ft_substr(input, start, *i - start);
    if (!value)
        syntax_error("failure assigning 'value' in lex_word function"); // Free when error;
    token = token_new(WORD, value);
    if (!token)
        syntax_error("failure assigning 'token' in lex_word function"); // Free when error;
    token_add_back(tokens, token);
}

void    lex_word(t_shell *data, char *input, int *i, t_token **tokens)
{
	char	*word;
	char	*segment;
	char	*tmp;
	char	*temp;

	word = ft_strdup("");
	temp = ft_calloc(2, sizeof(char));
	if (!word)
		return;
	while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
	{
		if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
		{
			segment = quote_handler(input, i);
			if (!segment)
			{
 				free(word);
				return ;
			}
			tmp = word;
			word = ft_strjoin(word, segment);
			free(tmp);
			free(segment);
		}
		else
		{
			temp[0] = input[*i];
			temp[1] = '\0';
			word = ft_strjoin(word, temp);
			(*i)++;
		}
	}
    token_add_back(tokens, token_new(WORD, word));
}

// void lex_word(char *input, int *i, t_token **tokens)
// {
//  	int		start;

// 		start = *i;
//     while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
// 	{
//         if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
// 		{
// 			if (!quote_handler(input, i))
// 				return ;
//             //else continue; // so when the quote is finsihed the token is created
// 		}
// 		else
// 			(*i)++;
// 	}
// 	create_token(input, i, start, tokens);
// }

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

void    lex_operator(char *input, int *i, t_token **tokens)
{
    t_token *token;

    token = NULL;
    if (input[*i] == '|')
        token = token_new(PIPE, "|");
    else if (input[*i] == '>' && input[(*i) + 1] != '>')
        token = token_new(REDIR_OUT, ">");
    else if (input[*i] == '<' && input[(*i) + 1] != '<')
        token = token_new(REDIR_IN, "<");
    else if (input[*i] == '>' && input[(*i) + 1] == '>')
    {
        token = token_new(APPEND, ">>");
        (*i)++;
    }
    else if (input[*i] == '<' && input[(*i) + 1] == '<')
    {
        token = token_new(HEREDOC, "<<");
        (*i)++;
    }
    (*i)++;
    token_add_back(tokens, token);
}

/*
 * DESCRIPTION 
 * Converts the received input into tokens and prepares them for parsing.
 * 
 * NOTE
 * Helper functions were created to make the code more readble.
 */

void	lexer(t_shell *data, char *input)   // should be called tokeniser??
{
	t_token *tokens;
    size_t  input_len;
    int     i;

//  if (validity_check(input) == 0 / 1);
//      return (error);
	ft_memset(&tokens, 0, sizeof(tokens));
    input_len = ft_strlen(input);
    i = 0;
	while ((size_t)i < input_len)   // could only be input[i] but that way is safer
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

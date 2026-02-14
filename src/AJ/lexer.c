/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/14 14:02:50 by azielnic         ###   ########.fr       */
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
 
// int validate_input(char* input) // returns true or false, false should print an error
// {
// not in quotes
// inside single quotes
// inside double quotes
// }


// decide how to design the error should it be a void or an int should it exit here or not 
// int	syntax_error(char *message)
// {
// 	ft_putstr_fd("Syntax error: ", 2);
// 	ft_putendl_fd(message, 2);
// 	return (0);
// }

int ft_is_operator(int c)
{
    return (c == '|' || c == '<' || c == '>');
}

int ft_isspace(int c)
{
    return (c == ' ');   // could include more whitespaces
}

/*
 * GENERAL: Adds a new token to the end of the current token list. Function name 
 *			says what the functions does (add) and where it does it (back) 
 *			applying it to tokens.
 * 
 * NOTE:	t_token **list is a pointer to the head pointer of the list.
 *			In case the list is empty it is needed so the head can be updated.
 *			t_token *new is the token to be added.
 * 
 * INFO:	Common in linked list naming conventions:
 *			- add_front → adds at the head (beginning)
 *			- add_back → adds at the tail (end)
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
 * GENERAL: Combines the gathered info and ONLY creates a new node.
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

int	quote_handler(char *input, int *i)
{	
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (!input[*i])
		{
			syntax_error("unclosed single quote");
			return (0);
		}
		(*i)++;
	}
	// // allow escaped quotes (\") to be skipped??
	else if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (!input[*i])
		{
			syntax_error("unclosed double quote");
			return (0);
		}
		(*i)++;
	}
	return (1);
}

void lex_word(char *input, int *i, t_token **tokens)
{
 	int		start;

	start = *i;
    while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
	{
        if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
		{
			if (!quote_handler(input, i))
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
 * GENERAL: Converts the received input into tokens and prepares them for parsing.
 * 
 * NOTE:    Helper functions were created to make the code more readble.
 */

t_token	*lexer(char *input)
{
	t_token *tokens;
    size_t  input_len;
    int     i;

	tokens = NULL; // memset?
    input_len = ft_strlen(input);
    i = 0;
	while ((size_t)i < input_len) // could only be input[i] but that way is safer
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
    return (tokens);
}

// int main(void)
// {
//     char *line = "echo blub \"hello world\"blabla ls -l || cat <<< e";
//     t_token *tokens = lexer(line);

//     while (tokens)
//     {
//         printf("TYPE=%d VALUE=%s\n", tokens->type, tokens->value);
//         tokens = tokens->next;
//     }
//     return (0);
// }

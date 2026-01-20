/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/18 22:35:44 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*  NEXT TO_DOs 
    
    - Validity check (e.g all operations or only quotes), maybe with copy of the original string
    - Check for single and double quotes validity by going through the string and checking for start and end
    - e.g. with strdup_section(char *string itself, int start, int end) 
 */

/* INPUT CHECKER
 *     --> validate_input() checks:
 *      -Control characters
 *      -Unsupported operators
 *      -Unclosed quotes
 */
 
/* LEXER
 * The lexer transforms a raw input string into a linked list of tokens 
 * (words and operators) that are easier to parse. --> Only tokenises
 */

/* PARSER
 * ????? --> Only interprets structure 
 */
 
// int validate_input(char* input) // returns true or false, false should print an error
// {
// not in quotes
// inside single quotes
// inside double quotes
// }

int ft_is_operator(int c)
{
    return (c == '|' || c == '<' || c == '>');
}

int ft_isspace(int c)
{
    return (c == ' ');   
}

/*
 * GENERAL: Adds a new tok
TYPE=0 VALUE=-l"en to the end of the current token list. Tells what 
 * it does (add) and where it does it (back) applying it to tokens.
 * 
 * NOTE:    t_token **list is a pointer to the head pointer of the list.
 *          In case the list is empty it is needed so the head can be updated.
 *          t_token *new is the token to be added.
 * 
 * INFO:    Common in linked list naming conventions:
 *              - add_front → adds at the head (beginning)
 *              - add_back → adds at the tail (end)
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

t_token *token_new(/* t_token_type type, */ int type, char *value)
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

void lex_word(char *input, int *i, t_token **tokens)
{
    int     start;
    char    *value;
    t_token *token;

    start = *i;
    while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
        (*i)++;
    value = ft_substr(input, start, *i - start);
    if (!value)
        write(1, "A\n", 2); // Free when error;
    token = token_new(WORD, value);
    if (!token)
        write(1, "b\n", 2); // Free when error;
    token_add_back(tokens, token);
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
 * NOTE:    Helper functions were created to make the code more readble. Can also 
 *          be left out and incorporated directly into the code. Any thoughts on this?
 */

t_token	*lexer(char *input)
{
	t_token *tokens;
    size_t input_len;
    int	i;

	tokens = NULL;
    input_len = ft_strlen(input);
    i = 0;
	while ((size_t)i < input_len) // could only be input[i] but that way is safer
	{
		if (ft_isspace(input[i])) // cast to unsigned char to avoid undefined behaviour?
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

int main(void)
{
    char *line = "ls -l || cat <<< e";
    t_token *tokens = lexer(line);

    // struct needs to be initialised with zero
    while (tokens)
    {
        printf("TYPE=%d VALUE=%s\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
    return (0);
}

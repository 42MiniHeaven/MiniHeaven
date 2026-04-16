/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/13 15:57:49 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	ft_is_operator(int c)
{
    return (c == '|' || c == '<' || c == '>');
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
 * DESCRIPTION
 * Adds a new token to the end of the current token list. Function name says 
 * what the functions does (add) and where it does it (back) applying it to 
 * tokens.
 * 
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

    value = NULL; // added later
    token = NULL; // added later
	value = ft_substr(input, start, *i - start);
    if (!value)
        syntax_error(token->value);
    token = token_new(WORD, value);
    if (!token)
        syntax_error(token->value);
    token_add_back(tokens, token);
}

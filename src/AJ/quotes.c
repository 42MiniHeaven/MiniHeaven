/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/13 22:26:27 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

// char	*create_segment(char *input, int *i, int start)
// {
// 	char    *segment;
// 	int		end;
	
// 	end = *i - 1;
// 	segment = ft_substr(input, start + 1, end - (start + 1));
//     if (!segment)
// 		syntax_error("failure assigning 'segment' in the quote handler");
// 	return (segment);
// }

// char	*handle_double_quote(char *input, int *i)
// {
// 	char	*segment;
// 	int		start;
	
// 	segment = ft_strdup("");
// 	start = *i;
// 	// allow $VAR expansion and $? expansion
// 	(*i)++;
// 	while (input[*i] && input[*i] != '"')
// 	{
// 		// if (input[*i] == '$')
// 		// 	expander(); //
// 		(*i)++;
// 	}
// 	if (!input[*i])
// 	{
// 		syntax_error("unclosed double quote");
// 		// set exit status to 2
// 		return (0);
// 	}
// 	(*i)++;
// 	return (segment);
// }

// char	*handle_single_quote(char *input, int *i)
// {
// 	char	*segment;
// 	int		start;
	
// 	segment = ft_strdup("");
// 	start = *i;
// 	(*i)++;
// 	while (input[*i] && input[*i] != '\'')
// 		(*i)++;
// 	if (!input[*i])
// 	{
// 		syntax_error("unclosed single quote");
// 		// set exit status to 2
// 		return (0);
// 	}
// 	(*i)++;
// 	segment = create_segment(input, i, start); // call create_literal_segment??
// 	return (segment);
// }

// char	*quote_handler(char *input, int *i)
// {	
// 	char	*buffer;
// 	char	*segment;

// 	buffer = ft_strdup("");
// 	segment = ft_strdup("");
// 	if (!buffer)
// 		return (NULL);
// 	if (input[*i] == '\'')
// 		segment = handle_single_quote(input, i);
// 	else if (input[*i] == '"')
// 		segment = handle_double_quote(input, i);
// 	return (segment);
// }

///////////////////////////// SIMPLE QUOTE HANDLER /////////////////////////

/*
 * DESCRIPTION
 * Recognises quotes to preserve quoted substrings so spaces/operators inside 
 * quotes don’t split tokens. This happens before tokenisation.
 */

// int	lex_quotes(char *input, int *i)
// {
// 	if (input[*i] == '\'')
// 	{
// 		(*i)++;
// 		while (input[*i] && input[*i] != '\'')
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			syntax_error("unclosed single quote");
// 			// set exit code
// 			return (0);
// 		}
// 		(*i)++;
// 	}
// 	else if (input[*i] == '"')
// 	{
// 		(*i)++;
// 		while (input[*i] && input[*i] != '"')
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			syntax_error("unclosed double quote");
// 			// set exit code
// 			return (0);
// 		}
// 		(*i)++;
// 	}
// 	return (1);
// }

int	lex_quotes(char *input, int *i)
{	
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		syntax_error("unclosed quote");
		// set exit code
		return (0);	
	}
	(*i)++;
	return (1);
}

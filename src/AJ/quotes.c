/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/12 20:35:32 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

char	*create_segment(char *input, int *i, int start)
{
	char    *segment;

	segment = ft_substr(input, start, *i - start);
    if (!segment)
		syntax_error("failure assigning 'segment' in the quote handler");
	return (segment);
}

char	*handle_single_quote(char *input, int *i)
{
	char	*segment;
	int		start;
	
	segment = ft_strdup("");
	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
	{
		syntax_error("unclosed single quote");
		// set exit status to 2
		return (0);
	}
	(*i)++;
	segment = create_segment(input, i, start);
	return (segment);
}

char	*quote_handler(char *input, int *i)
{	
	char	*buffer;
	char	*segment;

	buffer = ft_strdup("");
	segment = ft_strdup("");
	if (!buffer)
		return (NULL);
	if (input[*i] == '\'')
		segment = handle_single_quote(input, i);		
	// allow escaped quotes (\") to be skipped??
	// else if (input[*i] == '"')
	// {
	// 	// allow $VAR expansion and $? expansion
	// 	(*i)++;
	// 	while (input[*i] && input[*i] != '"')
	// 		(*i)++;
	// 	if (!input[*i])
	// 	{
	// 		syntax_error("unclosed double quote");
	// 		// set exit status to 2
	// 		return (0);
	// 	}
	// 	(*i)++;
	// }
	return (segment);
}

///////////////////////////// SIMPLE QUOTE HANDLER /////////////////////////

// int	quote_handler(char *input, int *i)
// {	
// 	if (input[*i] == '\'')
// 	{
// 		(*i)++;
// 		while (input[*i] && input[*i] != '\'')
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			syntax_error("unclosed single quote");
// 			return (0);
// 		}
// 		(*i)++;
//         // here it should be send to a function which trims the quotes
//         // and sends it back here to create the token
//         // this function should be universal and remove quotes in general
// 	}
// 	// // allow escaped quotes (\") to be skipped??
// 	else if (input[*i] == '"')
// 	{
// 		(*i)++;
// 		while (input[*i] && input[*i] != '"')
// 			(*i)++;
// 		if (!input[*i])
// 		{
// 			syntax_error("unclosed double quote");
// 			return (0);
// 		}
// 		(*i)++;
// 	}
// 	return (1);
// }

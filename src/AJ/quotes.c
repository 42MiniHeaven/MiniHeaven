/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/23 14:56:40 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"


// ******************************** EXPANDER **********************************




// ********************************* LEXER ************************************

/*
 * DESCRIPTION
 * Checks for unclosed quotes before the creating tokens.
 */

bool	lex_quotes(char *input, int *i)
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
		return (false);	
	}
	(*i)++;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/25 20:20:33 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

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
        // here it should be send to a function which trims the quotes
        // and sends it back here to create the token
        // this function should be universal and remove quotes in general
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

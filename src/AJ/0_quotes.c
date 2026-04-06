/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/06 20:47:41 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * QUOTE HANDLING
 * Quotes are handled in the lexer by checking unclosed quotes and in the 
 * expander by removing not needed quotes after expansion.
 */

// ********************************* LEXER ************************************

/*
 * DESCRIPTION
 * Checks for unclosed quotes before the creating tokens.
 */

bool	lex_unclosed_quotes(char *input, int *i)
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
 
// ******************************** EXPANDER **********************************

/*
 * DESCRIPTION
 * Function exists for the remove_quotes() funtion to check the length of the 
 * new string without the quotes. It uses the mask and substracts the number of 
 * quotes.
 */

static int	count_len(char *mask)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	while (mask[i])
	{
		if (mask[i] != 'Q')
			len++;
		i++;
	}
	return(len);
}

static char	*remove_quotes(char *word, char *mask)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(count_len(mask) + 1, sizeof(char));
	if (!result)
		return (NULL); // do we need an error?
	while (word[j] && mask[j])
	{
		while (mask[j] && mask[j] == 'Q')
			j++;
		result[i] = word[j];
		i++;
		j++;
	}
	return (result);
}

bool	quotes_removal(char **argv)
{
	int		i;
	char	*mask;
	char	*tmp;

	if (!argv)
		return (true);
	i = 0;
	if (!argv)
		return (true);
	while (argv[i])
	{
		mask = create_mask(argv[i]);
		tmp = remove_quotes(argv[i], mask);
		if (!tmp)
			return (free(mask), false);
		free(argv[i]);
		free(mask);
		argv[i] = tmp;
		i++;
	}
	return (true);
}

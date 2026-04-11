/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/11 23:21:44 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

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

int	count_len(char *mask)
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
	return (len);
}

char	*remove_quotes(char *word, char *mask)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(count_len(mask) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (word[j] && mask[j])
	{
		while (word[j] && mask[j] && mask[j] == 'Q')
			j++;
		if (!word[j] || !mask[j])
		{
			break ;
		}
		result[i++] = word[j++];
	}
	return (result);
}

static bool	needs_quote_removal(char *mask)
{
	if (!ft_strchr(mask, 'Q'))
		return (false);
	return (true);
}

bool	resolve_quotes(char **argv)
{
	int		i;
	char	*mask;
	char	*tmp;

	if (!argv)
		return (false);
	i = 0;
	while (argv[i])
	{
		mask = create_mask(argv[i]);
		if (!mask)
			return (false);
		if (needs_quote_removal(mask))
		{
			tmp = remove_quotes(argv[i], mask);
			if (!tmp)
				return (free(mask), false);
			free(argv[i]);
			argv[i] = tmp;
		}
		free(mask);
		i++;
	}
	return (true);
}
